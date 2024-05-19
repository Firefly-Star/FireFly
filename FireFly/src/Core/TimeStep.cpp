#include "ffpch.h"

#include "TimeStep.h"

#include "OS/OSAPI.h"
#include "Platform/Windows/WindowsTimeStep.h"

namespace FireFly
{
	TimeStep::TimeStep()
		: m_DeltaTime(1/60.0f), m_LastTime(0.0f)
	{

	}

	TimeStep* TimeStep::Create()
	{
		switch (OSAPI::GetOSAPI())
		{
		case OSAPI::OS::Windows: return new WindowsTimeStep();
		}
		FF_CORE_ASSERT(false, "Unknown OS!");
		return nullptr;
	}
}