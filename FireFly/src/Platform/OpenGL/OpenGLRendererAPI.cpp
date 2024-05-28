#include "ffpch.h"

#include "OpenGLRendererAPI.h"
#include "OpenGLError.h"

namespace FireFly
{
	void OpenGLRendererAPI::SetClearColor(float* color)
	{
		GLCALL(glClearColor(color[0], color[1], color[2], color[3]));
	}

	void OpenGLRendererAPI::Clear()
	{
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRendererAPI::Init()
	{
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCALL(glEnable(GL_DEPTH_TEST));
	}

	void OpenGLRendererAPI::SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		GLCALL(glViewport(x, y, width, height));
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