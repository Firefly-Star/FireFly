#pragma once

#include "Core/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace FireFly
{
	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_Window;
	};

}