#include "ffpch.h"

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"


#include "Renderer/Renderer.h"
//TEMP
#include "Platform/OpenGL/OpenGLError.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
//TEMP


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
		m_Input = Input::Create(window_ptr);
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
			m_LayerStack.OnUpdate();

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