#include "ffpch.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FireFly
{
	
	//--------Renderer-------------

	Renderer::SceneData Renderer::s_SceneData = { glm::mat4(1.0f) };

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
		RendererCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RendererCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::Render(Ref<VertexArray> vertexarray)
	{
		RendererCommand::PreForRender(vertexarray);

		RendererCommand::Upload(vertexarray, s_SceneData);



		RendererCommand::DrawIndexed(vertexarray);
	}

	//----------Renderer2D-----------
	struct Renderer2DPrimitives
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DPrimitives* s_Renderer2DPrimitives = nullptr;

	void Renderer2D::Init()
	{
		s_Renderer2DPrimitives = new Renderer2DPrimitives();

		Ref<VertexArray>& vertexArray = s_Renderer2DPrimitives->vertexArray;
		Ref<Shader>& shader = s_Renderer2DPrimitives->shader;


		vertexArray = VertexArray::Create();
		vertexArray->Bind();

		shader = Shader::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Shaders/PureColor.glsl");
		vertexArray->SetShader(shader);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		vertexArray->SetVertexBuffer(vertices, 12 * sizeof(float));

		BufferLayout* layout = vertexArray->GetBufferLayout();

		layout->Push({ "Position", FireFly::LayoutElementType::Float3 });

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		vertexArray->SetIndexBuffer(indices, 6 * sizeof(unsigned int));
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
		Ref<Shader>& shader = s_Renderer2DPrimitives->shader;

		shader->Bind();
		shader->UploadUniform(camera.GetPVmatrix(), "u_PVmatrix");
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	{
		Ref<VertexArray>& vertexArray = s_Renderer2DPrimitives->vertexArray;
		Ref<Shader>& shader = s_Renderer2DPrimitives->shader;

		RendererCommand::PreForRender(vertexArray);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		shader->UploadUniform(color.x, color.y, color.z, color.w, "u_Color");
		shader->UploadUniform(transform, "u_Model");
		RendererCommand::DrawIndexed(vertexArray);
	}


	//----------RendererCommand------
	Ref<RendererAPI> RendererCommand::s_RendererAPI = std::shared_ptr<RendererAPI>(RendererAPI::Create());

	void RendererCommand::SetClearColor(glm::vec4 color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::ClearColor()
	{
		s_RendererAPI->ClearColor();
	}

	void RendererCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RendererCommand::SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		s_RendererAPI->SetViewPort(x, y, width, height);
	}

	void RendererCommand::PreForRender(Ref<VertexArray> vertexarray)
	{
		s_RendererAPI->PreForRender(vertexarray);
	}

	void RendererCommand::Upload(Ref<VertexArray> vertexarray, const Renderer::SceneData& scenedata)
	{
		s_RendererAPI->UploadUniform(vertexarray, scenedata.PVmatrix, "u_PVmatrix");
	}

	void RendererCommand::DrawIndexed(Ref<VertexArray> vertexarray)
	{
		s_RendererAPI->DrawIndexed(vertexarray);
	}

	//---------RendererAPI--------
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		switch (s_API)
		{
		case (API::OpenGL): return new OpenGLRendererAPI();
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	
}