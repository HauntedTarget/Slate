#include "Enemy.h"
#include "Framework/Scene.h"
#include "Game/Player.h"
#include "Game/Lazer.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/ModelManager.h"
#include <Framework/Emitter.h>
#include "Input/InputSystem.h"

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

		m_fireTimer = bls::randomf(1.0f - (m_curGame->GetWave() * 0.001f), 2.0f - (m_curGame->GetWave() * 0.001f));

		if (m_fireTimer <= 0.001f) m_fireTimer = 0.001f;

		//Create Weapon
		bls::Transform transform{m_transform.position, m_transform.rotation, m_transform.scale * 0.5f};

		std::unique_ptr<Lazer> beam = std::make_unique<Lazer>(400.0f, transform, bls::g_modelLib.Get("Lazer.txt"));
		beam->m_tag = "UnFriendly";
		m_scene->Add(std::move(beam));

	}


	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forword * 1 * m_speed * dt;
	m_transform.position.x = bls::Wrap(m_transform.position.x, (float)bls::g_renderer.GetWidth());
	m_transform.position.y = bls::Wrap(m_transform.position.y, (float)bls::g_renderer.GetHeight());
}

void Enemy::OnCollision(GameObject* object)
{
	if (object->m_tag == "Friendly" && !object->m_destroyed)
	{
		bls::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = bls::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = bls::Color{ 1, 1, 1, 1 };
		bls::Transform transform{ { this->m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<bls::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));

		m_curGame->m_enemiesKilled++;

		m_destroyed = true;
	}
}
