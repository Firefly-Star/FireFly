#include "ffpch.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ImGuiLayer.h"
#include "Core/Application.h"

namespace FireFly
{
	ImGuiLayer::ImGuiLayer(const std::string& name)
		:Layer(name)
	{
		m_Window = (void*)Application::GetInstance()->GetWindow().GetWindowHandle();
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	//Should Set m_Window before call "OnAttach()"  
	void ImGuiLayer::OnAttach()
	{
		GLFWwindow* window = (GLFWwindow*)m_Window;
		FF_CORE_ASSERT(window && !glfwWindowShouldClose(window) && glfwGetCurrentContext() == window, "Invalid Window!")

		if (!ImGui::GetCurrentContext())
		{
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			ImGui::StyleColorsDark();

			io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
			io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}
	}

	void ImGuiLayer::OnUpdate()
	{
		

		ImGuiIO& io = ImGui::GetIO();

		Application* app = Application::GetInstance();

		io.DisplaySize = ImVec2(2*(float)app->GetWindow().GetWidth(), 2*(float)app->GetWindow().GetHeight());

		float time = float(glfwGetTime());
		io.DeltaTime = m_Time != 0 ? (time - m_Time) : (1 / 60.0f);
		m_Time = time;

		//ImGui::ShowDemoWindow();
		ImGui::Begin("type");
		char a[100] = "Hello World!";
		ImGui::InputText("test", a, 100);
		ImGui::End();

		ImGui::Render();
	}

	void ImGuiLayer::OnDettach()
	{

	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application* app = Application::GetInstance();
		io.DisplaySize = ImVec2((float)app->GetWindow().GetWidth(), (float)app->GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		if (true)
		{

		}
		ImGui::End();

	}
}