#include "ffpch.h"

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"

//TEMP
#include <glad/glad.h>
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
		m_ImGuiLayer = new ImGuiLayer("ImGui", window_ptr);
		m_ImGuiLayer->OnAttach();

		//TEMP
		std::string vs =R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec4 v_Color;	
		
		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
			v_Color = a_Color;
		}
		)";

		std::string fs = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec4 v_Color;
		
		void main()
		{
			color = v_Color;
		}
		)";

		vertexarray = VertexArray::Create();
		vertexarray->Bind();

		vertexarray->SetShader(vs, fs);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
		};
		
		vertexarray->SetVertexBuffer(vertices, 21 * 4);
		
		BufferLayout* layout = vertexarray->GetBufferLayout();

		layout->Push({ "Position", LayoutElementType::Float3 });
		layout->Push({ "Color", LayoutElementType::Float4 });
		
		unsigned int indices[] =
		{
			0, 1, 2
		};
		
		vertexarray->SetIndexBuffer(indices, 3 * 4);

		vertexarray->PreForRender();
		//TEMP
	}

	Application::~Application()
	{
		//TEMP
		delete vertexarray;
		//TEMP
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			vertexarray->Render();

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