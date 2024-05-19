#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#include "TimeStep.h"

namespace FireFly 
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		inline const Window* GetWindow() { return m_Window.get(); }
		inline const Input* GetInput() { return m_Input.get(); }
		inline const TimeStep* GetTimeStep() { return m_TimeStep.get(); }
	private:
		bool OnEvent(Event& e);
		bool OnClose(WindowCloseEvent& e);
	private:
		Ref<Window> m_Window;
		Ref<Input> m_Input;
		Ref<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		Ref<TimeStep> m_TimeStep;
	};

	//To be defined in the CLIENT(Sandbox)
	Application* CreateApplication();

}