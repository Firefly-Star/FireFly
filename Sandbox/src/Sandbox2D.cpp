#include "Sandbox2D.h"
#include "imgui.h"


Sandbox2D::Sandbox2D(const char* name)
	:Layer(name), m_Cameracontroller(1.6f, 1.0f), m_Color({0.2f, 0.8f, 0.3f, 1.0f})
{
	m_Texture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/Robin.jpg");
}

void Sandbox2D::OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
{
	m_Cameracontroller.OnUpdate(ts, input);
	FireFly::Renderer2D::BeginScene(m_Cameracontroller.GetCamera());
	FireFly::Renderer2D::DrawQuads({ 0.4f, 0.2f, 0.0f }, { 0.5f, 0.5f }, m_Color);
	FireFly::Renderer2D::DrawQuads({ 0.0f, 0.0f, -0.1f }, { 5.0f, 3.0f }, m_Texture, m_Color);
	FireFly::Renderer::EndScene();
}

bool Sandbox2D::OnEvent(FireFly::Event& e)
{
	m_Cameracontroller.OnEvent(e);
	return false;
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("BG Color", &m_Color[0]);
	ImGui::End();
}