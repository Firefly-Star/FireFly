#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace FireFly
{
	class Layer
	{
	public:
		Layer(const std::string& name = "layer", void* window = nullptr) :m_Name(name), m_Window(window) {}
		virtual ~Layer(){}

		virtual void OnUpdate(){}
		virtual bool OnEvent(Event& e) { return e.IsHandled(); }
		virtual void OnAttach(){}
		virtual void OnRender() {}
		virtual void OnDettach(){}
		inline void* GetWindow() { return m_Window; }
	protected:
		std::string m_Name;
		void* m_Window;
	};
}