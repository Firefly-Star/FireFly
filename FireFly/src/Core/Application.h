#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Window.h"
#include "LayerStack.h"

namespace FireFly 
{
	class FF_API Application
	{
	public:
		static Application* GetInstance();

		static void ReleaseInstance();

		Application(const Application&) = delete;

		Application& operator=(const Application&) = delete;

		void Run();

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
	protected:
		Application();
		virtual ~Application();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnEvent(Event& e);
		bool OnClose(WindowCloseEvent& e);

		static Application* app;

		LayerStack m_LayerStack;
	};
	


	//To be defined in the CLIENT(Sandbox)
	Application* CreateApplication();

}