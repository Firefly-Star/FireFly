#include "ffpch.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FireFly
{
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

}