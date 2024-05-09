#pragma once

#include "Core/Core.h"

namespace FireFly
{
	class FF_API Input
	{
	public:
		Input(void* window): m_Window(window) {}
		virtual bool IsKeyPressed(int keycode) = 0;
		virtual bool IsMousePressed(int button) = 0;
		virtual std::pair<float, float> GetMousePos() = 0;
	protected:
		void* m_Window;
	};
}