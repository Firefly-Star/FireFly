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
	
	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexarray)
	{
		vertexarray->PreForRender();
		vertexarray->Render();
	}
}