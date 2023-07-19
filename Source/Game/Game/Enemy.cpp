#include "Enemy.h"
#include "Framework/Scene.h"
#include "Game/Player.h"
#include "Game/Lazer.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"

void Enemy::Update(float dt)
{
	GameObject::Update(dt);

	Player* player = m_scene->GetGameObject<Player>();
	if (player) 
	{
		bls::Vector2 direction = player->m_transform.position - this->m_transform.position;
		m_transform.rotation = direction.Angle() + bls::DegreesToRadians(90);
	}

	m_fireTimer -= dt;
	if (m_fireTimer <= 0) 
	{

		m_fireTimer = bls::randomf(2.0f,4.0f);

		//Create Weapon
		bls::Transform transform{m_transform.position, m_transform.rotation, m_transform.scale * 0.5f};
		std::unique_ptr<Lazer> beam = std::make_unique<Lazer>(400.0f, transform, m_model);
		m_scene->Add(std::move(beam));

	}


	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forword * 1 * m_speed * dt;
	m_transform.position.x = bls::Wrap(m_transform.position.x, (float)bls::g_renderer.GetWidth());
	m_transform.position.y = bls::Wrap(m_transform.position.y, (float)bls::g_renderer.GetHeight());
}
