#include "ffpch.h"

#include "WindowsTimeStep.h"

#include <GLFW/glfw3.h>

namespace FireFly
{
	WindowsTimeStep::WindowsTimeStep()
		:TimeStep()
	{
	}

	void WindowsTimeStep::OnUpdate()
	{
		float nowTime = (float)glfwGetTime();

		m_DeltaTime = nowTime - m_LastTime;
		m_LastTime = nowTime;
	}
}