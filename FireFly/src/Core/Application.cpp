#include "ffpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/WindowEvent.h"
#include "Log.h"

//TEMP
#include "Platform/OpenGL/OpenGLError.h"
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
		
		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
		}
		)";

		std::string fs = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		
		void main()
		{
			color = vec4(0.8, 0.2, 0.3, 1.0);
		}
		)";

		shader = Shader::Create(vs, fs);
		shader->Bind();

		GLCALL(glGenVertexArrays(1, &vertexarray));
		GLCALL(glBindVertexArray(vertexarray));

		GLCALL(glEnableVertexAttribArray(0));
		
		
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		
		vertexbuffer = VertexBuffer::Create(vertices, 9 * sizeof(float));
		
		GLCALL(glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));
		
		unsigned int indices[] =
		{
			0, 1, 2
		};
		
		indexbuffer = IndexBuffer::Create(indices, 3 * sizeof(unsigned int));
		//TEMP
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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