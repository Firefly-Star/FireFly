#include "ffpch.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FireFly
{
	//----RendererCommandQueue----

	RendererCommandQueue::RendererCommandQueue()
		:m_CommandCount(0)
	{
		m_RendererCommandBuffer = new byte[FF_BUFFER_SIZE];
		m_BufferWorkPtr = m_RendererCommandBuffer;
		memset(m_RendererCommandBuffer, 0, FF_BUFFER_SIZE);
	}

	RendererCommandQueue::~RendererCommandQueue()
	{
		delete[] m_RendererCommandBuffer;
		m_RendererCommandBuffer = nullptr;
		m_BufferWorkPtr = nullptr;
	}

	void RendererCommandQueue::SubmitCommand(CommandFunc fn, void* params, unsigned int size)
	{
		memcpy(m_BufferWorkPtr, &fn, sizeof(CommandFunc));
		m_BufferWorkPtr += sizeof(CommandFunc);
		memcpy(m_BufferWorkPtr, params, size);
		m_BufferWorkPtr += size;

		auto totalSize = sizeof(CommandFunc) + size;
		auto padding = totalSize % 16;
		m_BufferWorkPtr += 16 - padding;
		m_CommandCount++;
		//FF_CORE_TRACE("Renderer Command Queue: {0}commands, {1}bytes", m_CommandCount, m_BufferWorkPtr - m_RendererCommandBuffer);
	}

	void RendererCommandQueue::Execute()
	{
		//FF_CORE_TRACE("Renderer Command Queue: {0}commands, {1}bytes", m_CommandCount, m_BufferWorkPtr - m_RendererCommandBuffer);
		byte* workPtr = m_RendererCommandBuffer;

		for (unsigned int i = 1; i <= m_CommandCount; i++)
		{
			auto func = *(CommandFunc*)workPtr;
			workPtr += sizeof(CommandFunc);
			workPtr += func(workPtr);
			
			auto padding = (workPtr - m_RendererCommandBuffer) % 16;
			workPtr += 16 - padding;
		}

		m_BufferWorkPtr = m_RendererCommandBuffer;
		m_CommandCount = 0;
	}


	
	//--------Renderer-------------

	Renderer::SceneData Renderer::s_SceneData = { glm::mat4(1.0f) };
	RendererCommandQueue Renderer::s_RendererCommandQueue = RendererCommandQueue();

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
		unsigned int params[] = {0, 0, width, height};
		s_RendererCommandQueue.SubmitCommand(RendererCommand::SetViewPort, params, 4 * sizeof(unsigned int));
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		float params[] = { r, g, b, a };
		s_RendererCommandQueue.SubmitCommand(RendererCommand::SetClearColor, params, 4 * sizeof(float));
	}

	void Renderer::Clear()
	{
		s_RendererCommandQueue.SubmitCommand(RendererCommand::Clear, nullptr, 0);
	}

	void Renderer::Render(Ref<VertexArray> vertexarray)
	{
		RendererCommand::PreForRender(vertexarray);

		RendererCommand::Upload(vertexarray, s_SceneData);



		RendererCommand::DrawIndexed(vertexarray);
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
		RendererCommand::DrawIndexed(s_Renderer2DPrimitives->vertexArray);
	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, float rotation)
	{
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
		RendererCommand::DrawIndexed(s_Renderer2DPrimitives->vertexArray);
	}

	void Renderer2D::DrawQuads(glm::vec3 position, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color, float rotation)
	{
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
		RendererCommand::DrawIndexed(s_Renderer2DPrimitives->vertexArray);
	}

	//----------RendererCommand------
	Ref<RendererAPI> RendererCommand::s_RendererAPI = std::shared_ptr<RendererAPI>(RendererAPI::Create());

	unsigned int RendererCommand::SetClearColor(void* datapack)
	{
		s_RendererAPI->SetClearColor((float*)datapack);
		return 4 * sizeof(float);
	}

	unsigned int RendererCommand::Clear(void* datapack)
	{
		s_RendererAPI->Clear();
		return 0;
	}

	void RendererCommand::Init()
	{
		s_RendererAPI->Init();
	}

	unsigned int RendererCommand::SetViewPort(void* datapack)
	{
		unsigned int* params = (unsigned int*)datapack;
		s_RendererAPI->SetViewPort(params[0], params[1], params[2], params[3]);
		return 4 * sizeof(unsigned int);
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