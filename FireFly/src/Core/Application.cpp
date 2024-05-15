#include "ffpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"

namespace FireFly
{

	Application* Application::app = nullptr;

	Application* Application::GetInstance()
	{
		if (!app)
		{
			app = new Application();
		}
		return app;
	}

	void Application::ReleaseInstance()
	{
		if (app)
		{
			delete app;
			app = nullptr;
		}
	}

	Application::Application()
	{
		WindowProp prop(1600, 960);
		m_Window = Window::Create(prop);
		m_Window->SetEventCallback(FF_BIND_EVENT_FN(Application::OnEvent));
		void* window_ptr = m_Window->GetWindowHandle();
		m_ImGuiLayer = new ImGuiLayer("ImGui", window_ptr);
		m_ImGuiLayer->OnAttach();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto it : m_LayerStack.GetLayers())
			{
				it->OnUpdate();
			}

			for (auto it : m_LayerStack.GetOverLayers())
			{
				it->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			m_ImGuiLayer->OnRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	bool Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.EventDispatch<WindowCloseEvent>(FF_BIND_EVENT_FN(Application::OnClose));
		bool isHandled = m_LayerStack.OnEvent(e);
		
		return isHandled;
	}

	bool Application::OnClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}