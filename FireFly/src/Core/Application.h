#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

// TEMP
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
//TEMP

namespace FireFly 
{
	class Application
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
		const Input* GetInput() { return m_Input; }
	protected:
		Application();
		virtual ~Application();
	private:
		bool OnEvent(Event& e);
		bool OnClose(WindowCloseEvent& e);
	private:
		static Application* app;

		Window* m_Window;
		Input* m_Input;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		// TEMP
		VertexArray* vertexarray;
		OrthoCamera camera;
		//TEMP
	};

	//To be defined in the CLIENT(Sandbox)
	Application* CreateApplication();

}