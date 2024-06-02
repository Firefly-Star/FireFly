#pragma once

#include "FireFly.h"
#if 0
class Sandbox2D : public FireFly::Layer
{
public:
	Sandbox2D(const char* name = "Layer");
	virtual void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input) override;
	virtual void OnImGuiRender() override;
	virtual bool OnEvent(FireFly::Event& e) override;
private:
	FireFly::OrthoCameraController m_Cameracontroller;

	glm::vec4 m_Color;

	//TEMP
	FireFly::Ref<FireFly::Texture> m_Texture;
};
#endif