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
		:camera({-1.0f, 1.0f, -1.0f, 1.0f})
	{
		WindowProp prop(1600, 960);
		m_Window = Window::Create(prop);
		m_Window->SetEventCallback(FF_BIND_EVENT_FN(Application::OnEvent));
		void* window_ptr = m_Window->GetWindowHandle();
		m_Input = Input::Create(window_ptr);
		m_ImGuiLayer = new ImGuiLayer("ImGui", window_ptr);
		m_ImGuiLayer->OnAttach();

		//TEMP
		std::string vs = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec4 v_Color;	

		uniform mat4 u_PVmatrix;
		
		void main()
		{
			gl_Position = u_PVmatrix * vec4(a_Position, 1.0);
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
			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RendererCommand::ClearColor();

			camera.SetRotation(90.0f);

			Renderer::BeginScene(camera);
			Renderer::Render(vertexarray);

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