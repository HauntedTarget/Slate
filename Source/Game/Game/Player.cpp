#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{

	float rotate = 0, scale = 10, thrust = 0;

	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);

	m_transform.rotation += rotate * m_turnRate * dt;
	m_transform.scale = scale;
	m_transform.position += forword * thrust * m_speed * dt;
	m_transform.position.x = bls::Wrap(m_transform.position.x, (float)bls::g_renderer.GetWidth());
	m_transform.position.y = bls::Wrap(m_transform.position.y, (float)bls::g_renderer.GetHeight());
}
