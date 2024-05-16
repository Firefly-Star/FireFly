#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

// TEMP
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
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
	protected:
		Application();
		virtual ~Application();
	private:
		Window* m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		bool OnEvent(Event& e);
		bool OnClose(WindowCloseEvent& e);

		static Application* app;

		LayerStack m_LayerStack;

		// TEMP
		Shader* shader;
		VertexBuffer* vertexbuffer;
		IndexBuffer* indexbuffer;
		unsigned int  vertexarray;
		//TEMP
	};

	//To be defined in the CLIENT(Sandbox)
	Application* CreateApplication();

}