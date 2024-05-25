#pragma once

#include "FireFly.h"

class Sandbox2D : public FireFly::Layer
{
public:
	Sandbox2D(std::string name = "Layer");
	virtual void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input) override;
	virtual void OnImGuiRender() override;
	virtual bool OnEvent(FireFly::Event& e) override;
private:
	FireFly::OrthoCameraController m_Cameracontroller;

	glm::vec4 m_Color;
};