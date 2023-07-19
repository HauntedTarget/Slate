#include "Lazer.h"

void Lazer::Update(float dt)
{
	if (m_transform.position.x < -25 || m_transform.position.x > bls::g_renderer.GetWidth() + 25 ||
		m_transform.position.y < -25 || m_transform.position.y > bls::g_renderer.GetHeight() + 25)
	{
		m_destroyed = true;
	}
	GameObject::Update(dt);

	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forword * 1 * m_speed * dt;
}
