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
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Render(const VertexArray* vertexarray)
	{
		RendererCommand::DrawIndexed(vertexarray);
	}

	//----------RendererCommand------
	RendererAPI* RendererCommand::s_RendererAPI = RendererAPI::Create();

	void RendererCommand::SetClearColor(glm::vec4 color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::ClearColor()
	{
		s_RendererAPI->ClearColor();
	}

	void RendererCommand::DrawIndexed(const VertexArray* vertexarray)
	{
		s_RendererAPI->DrawIndexed(vertexarray);
	}

}