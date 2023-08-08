#include "Enemy.h"
#include "Framework/Scene.h"
#include "Game/Player.h"
#include "Game/Lazer.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include <Framework/Emitter.h>
#include "Input/InputSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Texture.h"

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

		m_fireTimer = bls::randomf(1.0f - (m_curGame->GetWave() * 0.01f), 2.0f - (m_curGame->GetWave() * 0.01f));

		if (m_fireTimer <= 0.01f) m_fireTimer = 0.01f;

		//Create Weapon
		bls::Transform transform{m_transform.position, m_transform.rotation, m_transform.scale * 0.5f};
		std::unique_ptr<Lazer> e_beam = std::make_unique<Lazer>(400.0f, transform);
		e_beam->m_tag = "UnFriendly";

		//Player Components Init
		std::unique_ptr<bls::SpriteComponent> component = std::make_unique<bls::SpriteComponent>();
		component->m_texture = bls::g_resources.Get<bls::Texture>("lazer.png", bls::g_renderer);
		e_beam->AddComponent(std::move(component));

		m_scene->Add(std::move(e_beam));



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
