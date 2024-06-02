#pragma once
#include <glm/glm.hpp>
#include <FireFly.h>
#include <cmath>
#if 0
#define PI 3.1415926f
class Speed
{
public:
	Speed(glm::vec2& v, float a);
	void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input);
	inline const glm::vec2& GetV() const { return m_V; }
private:
	glm::vec2 m_V;
	static float s_g;
	float m_A;
};

inline float V2Angle(Speed& v)
{
	return std::atan(v.GetV().y / v.GetV().x) / PI * 180.0f - 90.0f;
}

class Position
{
public:
	Position(glm::vec2& position, FireFly::Ref<Speed> speed);
	void OnUpdate(FireFly::Ref<FireFly::TimeStep> ts, FireFly::Ref<FireFly::Input> input);
	inline const FireFly::Ref<Speed> GetSpeed() { return m_Speed; }
	inline glm::vec2 GetPosition() { return m_Position; }
private:
	const FireFly::Ref<Speed> m_Speed;
	glm::vec2 m_Position;
};
#endif