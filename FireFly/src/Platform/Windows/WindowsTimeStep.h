#pragma once

#include "Core/TimeStep.h"

namespace FireFly
{
	class WindowsTimeStep : public TimeStep
	{
	public:
		WindowsTimeStep();
		virtual void OnUpdate() override;
	};
}