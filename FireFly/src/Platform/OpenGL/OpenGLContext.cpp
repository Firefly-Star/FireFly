#include "ffpch.h"
#include "Core/Core.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FireFly
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_Window(window)
	{
		FF_CORE_ASSERT(window, "The Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		FF_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!")

		FF_CORE_INFO("OpenGL Renderer: {1} vendored by {0}", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER));
		FF_CORE_INFO("OpenGL version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}