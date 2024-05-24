#include "ffpch.h"

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"


#include "Renderer/Renderer.h"


namespace FireFly
{
	Application::Application()
	{
		WindowProp prop(1600, 1600);
		m_Window.reset(Window::Create(prop));
		m_Window->SetEventCallback(FF_BIND_EVENT_FN(Application::OnEvent));
		void* window_ptr = m_Window->GetWindowHandle();
		m_Input.reset(Input::Create(window_ptr));
		m_ImGuiLayer = std::make_shared<ImGuiLayer>("ImGui", window_ptr);
		m_ImGuiLayer->OnAttach();

		m_TimeStep.reset(TimeStep::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_LayerStack.OnUpdate(m_TimeStep, m_Input);

			m_ImGuiLayer->Begin();
			m_LayerStack.OnImGuiRender();
			m_ImGuiLayer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

			m_TimeStep->OnUpdate();
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
		dispatcher.EventDispatch<WindowResizeEvent>(FF_BIND_EVENT_FN(Application::OnWindowResize));
		bool isHandled = m_LayerStack.OnEvent(e);
		
		return isHandled;
	}

	bool Application::OnClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}