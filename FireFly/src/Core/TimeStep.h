#pragma once

namespace FireFly
{
	class TimeStep
	{
	public:
		TimeStep();
		virtual ~TimeStep() {}

		static TimeStep* Create();
		virtual void OnUpdate() = 0;
		inline float GetDeltaTime() const { return m_DeltaTime; }
		inline float GetTime() const { return m_LastTime; }
	protected:
		float m_DeltaTime, m_LastTime;
	};
}