#pragma once

#include <FireFly.h>
#include "Speed.h"
#if 0
class Rocket
{
public:
	Rocket(glm::vec2 v, float a);
	void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input);
private:
	FireFly::Ref<FireFly::Texture> m_RocketTexture;
	Position m_Position;
};

class Triangle
{
public:
	Triangle(float up, float split, float dist);
	void OnUpdate();
	void SetPosition(float up, float split, float dist);
	inline float GetDist() { return m_Dist; }
private:
	FireFly::Ref<FireFly::Texture> m_UpTriangleTexture;
	FireFly::Ref<FireFly::Texture> m_DownTriangleTexture;
	float m_Up;
	float m_Split;
	float m_Dist;
};

class Triangles
{
public:
	Triangles(float width, float dist) ;
	void OnUpdate(float right);
private:
	std::vector<Triangle> m_Triangles;
	float m_Width;
	float m_Dist;
};

class GameLayer : public FireFly::Layer
{
public:
	GameLayer(float rightSpeed, float m_TriangleDist, const char* name = "layer");
	virtual ~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDettach() override;
	virtual void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input) override;
	virtual void OnImGuiRender() override;
	virtual bool OnEvent(FireFly::Event& e) override;
private:
	FireFly::Ref<Rocket> m_Rocket;
	Triangles m_Triangles;
	FireFly::Ref<FireFly::OrthoCamera> m_Camera;
	glm::vec2 m_Position;
	float m_RightSpeed;
	float m_TriangleDist;
};
#endif