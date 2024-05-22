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

	void OpenGLRendererAPI::PreForRender(const VertexArray* vertexarray)
	{
		vertexarray->PreForRender();
	}
	
	void OpenGLRendererAPI::UploadUniform(const VertexArray* vertexarray, const glm::mat4& mat, const std::string name)
	{
		vertexarray->GetShader()->UploadUniform(mat, name);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexarray)
	{
		vertexarray->Render();
	}
}