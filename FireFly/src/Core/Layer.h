#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace FireFly
{
	class FF_API Layer
	{
	public:
		Layer(const std::string& name = "layer") :m_Name(name) {}
		virtual ~Layer(){}

		virtual void OnUpdate(){}
		virtual bool OnEvent(Event& e) { return e.IsHandled(); }
		virtual void OnAttach(){}
		virtual void OnRender() {}
		virtual void OnDettach(){}
	private:
		std::string m_Name;
	};
}