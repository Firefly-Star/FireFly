#include "GameLayer.h"
#include <random>
#if 0
GameLayer::GameLayer(float rightSpeed, float m_TriangleDist, const char* name)
	:Layer(name), m_Triangles(0.1f, 0.3f)
{
	m_Rocket = std::make_shared<Rocket>(glm::vec2{ rightSpeed, 0.0f }, 2.0);
	m_Camera = std::make_shared<FireFly::OrthoCamera>(glm::vec4{ -1.0f, 1.0f, -1.0f, 1.0f });
	m_Position = glm::vec2(0.0f, 0.0f);
	m_RightSpeed = rightSpeed;
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDettach()
{
}

void GameLayer::OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
{
	m_Rocket->OnUpdate(ts, input);
	m_Triangles.OnUpdate(m_RightSpeed * ts->GetTime());
	m_Position.x += m_RightSpeed * ts->GetDeltaTime();
	m_Camera->SetPosition(glm::vec3(m_Position.x, m_Position.y, 0.0f));
	FireFly::Renderer2D::BeginScene(*m_Camera);
	FireFly::Renderer2D::DrawQuads({ m_RightSpeed * ts->GetTime(), -0.9 }, { 2.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	FireFly::Renderer2D::DrawQuads({ m_RightSpeed * ts->GetTime(),  0.9 }, { 2.0f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	//FF_CORE_INFO("{} fps", 1 / ts->GetDeltaTime());
}

void GameLayer::OnImGuiRender()
{
}

bool GameLayer::OnEvent(FireFly::Event& e)
{
	return false;
}

Rocket::Rocket(glm::vec2 v, float a)
	:m_Position(glm::vec2{0.0f, 0.0f}, std::make_shared<Speed>(v,a))
{
	m_RocketTexture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/RocketShip.png");
}

void Rocket::OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
{
	m_Position.OnUpdate(ts, input);
	FireFly::Renderer2D::DrawQuads(m_Position.GetPosition(), {0.1f, 0.2f}, m_RocketTexture, V2Angle(*m_Position.GetSpeed()));
	//FireFly::Renderer2D::DrawQuads({ 0.0f, 0.0f, 0.0f }, { 0.1f, 0.2f }, m_RocketTexture, -90);
}

Triangle::Triangle(float up, float split, float dist)
	:m_Dist(dist), m_Split(split), m_Up(up)
{
	m_UpTriangleTexture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/Triangles.png");
	m_DownTriangleTexture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/Triangles.png");
}

void Triangle::OnUpdate()
{
	FireFly::Renderer2D::DrawQuads({ m_Dist, (m_Up - m_Split) / 2 - 0.8f, 0.1f }, { 0.2, m_Up - m_Split }, m_DownTriangleTexture);
	FireFly::Renderer2D::DrawQuads({ m_Dist, m_Up / 2 , 0.1f }, { -0.2, -1.6 + m_Up}, m_UpTriangleTexture);
}

void Triangle::SetPosition(float up, float split, float dist)
{
	m_Dist = dist;
	m_Split = split;
	m_Up = up;
}

Triangles::Triangles(float width, float dist)
	:m_Width(width), m_Dist(dist)
{
	for (int i = 1; (i - 1) * dist <= 2.0 + 2 * width; i++)
	{
		m_Triangles.push_back(Triangle(0.85f + (float)rand() / RAND_MAX * 0.3f, 0.3f, 0.8f + (i - 1) * dist));
	}
}

void Triangles::OnUpdate(float right)
{
	for (auto& it : m_Triangles)
	{
		it.OnUpdate();
		if (it.GetDist() - right <= -1.0 - m_Width)
		{
			it.SetPosition(0.85f + (float)rand() / RAND_MAX * 0.3f, 0.3f, it.GetDist() + m_Triangles.size() * m_Dist);
		}
	}
}
#endif