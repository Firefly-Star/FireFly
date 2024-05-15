#pragma once

#include "Core/Input.h"

namespace FireFly
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput (void* window = nullptr) : Input(window) {}

		virtual bool IsKeyPressed(int keycode) override;
		virtual bool IsMousePressed(int button) override;
		virtual std::pair<float, float> GetMousePos() override;
	};
}