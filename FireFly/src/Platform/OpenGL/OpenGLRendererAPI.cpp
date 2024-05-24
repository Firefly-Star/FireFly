#include "ffpch.h"

#include "OpenGLRendererAPI.h"
#include "OpenGLError.h"

namespace FireFly
{
	void OpenGLRendererAPI::SetClearColor(glm::vec4 color)
	{
		GLCALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRendererAPI::ClearColor()
	{
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::PreForRender(Ref<VertexArray> vertexarray)
	{
		vertexarray->PreForRender();
	}
	
	void OpenGLRendererAPI::UploadUniform(Ref<VertexArray> vertexarray, const glm::mat4& mat, const std::string name)
	{
		vertexarray->GetShader()->UploadUniform(mat, name);
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> vertexarray)
	{
		vertexarray->Render();
	}
}