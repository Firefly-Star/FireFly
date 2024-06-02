#include "ffpch.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glm/gtc/matrix_transform.hpp>

#if 1
namespace FireFly
{
	//--------Renderer-------------

	Renderer::SceneData Renderer::s_SceneData = { glm::mat4(1.0f) };
	RendererCommandQueue Renderer::s_RendererCommandQueue = RendererCommandQueue();

	void Renderer::Submit(RendererCommandQueue::CommandFunc func, byte* params, unsigned int size, unsigned int alignment)
	{
		s_RendererCommandQueue.Submit(func, params, size, alignment);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		s_SceneData.PVmatrix = camera.GetPVmatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Init()
	{
		FF_RENDER({
			RendererAPI::Init();
			Renderer2D::Init();
			});
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		FF_RENDER_4({
			RendererAPI::SetClearColor(r, g, b, a);
			}, r, g, b, a);
	}

	void Renderer::Clear()
	{
		FF_RENDER({
			RendererAPI::Clear();
			})
	}

	void Renderer::Render(Ref<VertexArray> vertexarray)
	{
		FF_RENDER_2({
			RendererAPI::PreForRender(vertexarray);
			RendererAPI::UploadUniform(vertexarray, s_SceneData.PVmatrix, "u_PVmatrix");
			RendererAPI::DrawIndexed(vertexarray->GetCount());
			}, vertexarray, s_SceneData)
	}

	void Renderer::Render()
	{
		s_RendererCommandQueue.Execute();
	}

	//----------Renderer2D-----------
	struct Renderer2DPrimitives
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
		Ref<Texture> pureWhiteTexture;
	};

	static Renderer2DPrimitives* s_Renderer2DPrimitives = nullptr;

	void Renderer2D::Init()
	{
		s_Renderer2DPrimitives = new Renderer2DPrimitives();

		unsigned char data[] = { 255, 255, 255, 255 };
		s_Renderer2DPrimitives->pureWhiteTexture = Texture2D::Create();
		s_Renderer2DPrimitives->pureWhiteTexture->SetTexture(data, 1, 1);

		s_Renderer2DPrimitives->vertexArray = VertexArray::Create();
		s_Renderer2DPrimitives->vertexArray->Bind();

		s_Renderer2DPrimitives->shader = Shader::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Shaders/TextureShader2D.glsl");

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		s_Renderer2DPrimitives->vertexArray->SetVertexBuffer(vertices, 20 * sizeof(float));

		BufferLayout* layout = s_Renderer2DPrimitives->vertexArray->GetBufferLayout();

		layout->Push({ "Position", FireFly::LayoutElementType::Float3 });
		layout->Push({ "Texture Coord", FireFly::LayoutElementType::Float2 });

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		s_Renderer2DPrimitives->vertexArray->SetIndexBuffer(indices, 6 * sizeof(unsigned int));
	}

	void Renderer2D::Shutdowm()
	{
		delete s_Renderer2DPrimitives;
		s_Renderer2DPrimitives = nullptr;
	}

	void Renderer2D::BeginScene()
	{
	}

	void Renderer2D::BeginScene(OrthoCamera& camera)
	{
		Ref<Shader> shader = s_Renderer2DPrimitives->shader;

		shader->Bind();
		shader->UploadUniform(camera.GetPVmatrix(), "u_PVmatrix");
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuads(glm::vec2 position, glm::vec2 size, glm::vec4 color, float rotation)
	{
		DrawQuads(glm::vec3(position.x, position.y, 0.0f), size, color, rotation);
	}

	void Renderer2D::DrawQuads(glm::vec2 position, glm::vec2 size, Ref<Texture>& texture, float rotation)
	{
		DrawQuads(glm::vec3(position.x, position.y, 0.0f), size, texture, rotation);
	}

	void Renderer2D::DrawQuads(glm::vec2 position, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color, float rotation)
	{
		DrawQuads(glm::vec3(position.x, position.y, 0.0f), size, texture, color, rotation);
	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, glm::vec4 color, float rotation)
	{
		FF_RENDER_4({
			s_Renderer2DPrimitives->vertexArray->PreForRender();
			s_Renderer2DPrimitives->shader->Bind();
			glm::mat4 transform =
				glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
			s_Renderer2DPrimitives->pureWhiteTexture->Bind();

			s_Renderer2DPrimitives->shader->UploadUniform(0, "u_Texture");
			s_Renderer2DPrimitives->shader->UploadUniform(transform, "u_Model");
			s_Renderer2DPrimitives->shader->UploadUniform(color.x, color.y, color.z, color.w, "u_Color");
			RendererAPI::DrawIndexed(s_Renderer2DPrimitives->vertexArray->GetCount());
			}, position, size, color, rotation);
	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, float rotation)
	{
		FF_RENDER_4({
			s_Renderer2DPrimitives->vertexArray->PreForRender();
			s_Renderer2DPrimitives->shader->Bind();

			glm::mat4 transform =
				glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
			texture->Bind();

			s_Renderer2DPrimitives->shader->UploadUniform(0, "u_Texture");
			s_Renderer2DPrimitives->shader->UploadUniform(transform, "u_Model");
			s_Renderer2DPrimitives->shader->UploadUniform(1.0f, 1.0f, 1.0f, 1.0f, "u_Color");
			RendererAPI::DrawIndexed(s_Renderer2DPrimitives->vertexArray->GetCount());
			}, position, size, texture, rotation);
	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color, float rotation)
	{
		FF_RENDER_5({
			s_Renderer2DPrimitives->vertexArray->PreForRender();
			s_Renderer2DPrimitives->shader->Bind();

			glm::mat4 transform =
				glm::translate(glm::mat4(1.0f), position) *
				glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
			texture->Bind();

			s_Renderer2DPrimitives->shader->UploadUniform(0, "u_Texture");
			s_Renderer2DPrimitives->shader->UploadUniform(transform, "u_Model");
			s_Renderer2DPrimitives->shader->UploadUniform(color.r, color.g, color.b, color.a, "u_Color");
			RendererAPI::DrawIndexed(s_Renderer2DPrimitives->vertexArray->GetCount());
			}, position, size, texture, color, rotation);
	}
}
#endif