#include "Lazer.h"

void Lazer::Update(float dt)
{
	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forword * 1 * m_speed * dt;
	m_transform.position.x = bls::Wrap(m_transform.position.x, (float)bls::g_renderer.GetWidth());
	m_transform.position.y = bls::Wrap(m_transform.position.y, (float)bls::g_renderer.GetHeight());
}
