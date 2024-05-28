#include "Speed.h"

float Speed::s_g = 1.0f;

Speed::Speed(glm::vec2& v, float a)
	:m_V(v), m_A(a)
{

}

void Speed::OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
{
	if (input->IsKeyPressed(FF_KEY_W))
	{
		m_V.y += m_A * ts->GetDeltaTime();
	}
	else if (input->IsKeyPressed(FF_KEY_S))
	{
		m_V.y -= m_A * ts->GetDeltaTime();
	}
	m_V.y -= s_g * ts->GetDeltaTime();
}

Position::Position(glm::vec2& position, FireFly::Ref<Speed> speed)
	:m_Position(position), m_Speed(speed)
{
}

void Position::OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input)
{
	m_Speed->OnUpdate(ts, input);
	m_Position += ts->GetDeltaTime() * m_Speed->GetV();
}
