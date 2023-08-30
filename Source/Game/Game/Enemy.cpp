#include "Enemy.h"
#include "Framework/Framework.h"
#include "Game/Player.h"
#include "Game/Lazer.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Input/InputSystem.h"
#include "Renderer/Texture.h"

namespace bls
{
	CLASS_DEFINE(Enemy)

	bool Enemy::Initialize()
	{
		GameObject::Initialize();

		auto collisionComponent = GetComponent<bls::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<bls::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<bls::RenderComponent>()->GetRadius() * scale;
			}
		}

		return true;
	}

	void Enemy::Update(float dt)
	{
		GameObject::Update(dt);

		Player* player = m_scene->GetGameObject<Player>();
		if (player)
		{
			bls::Vector2 direction = player->transform.position - this->transform.position;
			transform.rotation = direction.Angle() + bls::DegreesToRadians(90);
		}

		m_fireTimer -= dt;
		if (m_fireTimer <= 0)
		{

			m_fireTimer = bls::randomf(1.0f - (m_curGame->GetWave() * 0.01f), 2.0f - (m_curGame->GetWave() * 0.01f));

			if (m_fireTimer <= 0.01f) m_fireTimer = 0.01f;

			auto weapon = INSTANTIATE(Lazer, "Beam");
			weapon->transform = { transform.position, transform.rotation, transform.scale * 0.5f };
			weapon->Initialize();
			weapon->tag = "UnFriendly";
			m_scene->Add(std::move(weapon));

			/*
			//Create Weapon
			bls::Transform transform{transform.position, transform.rotation, transform.scale * 0.5f};
			std::unique_ptr < bls::LazerComponent > e_beam = std::make_unique<LazerComponent>(400.0f, transform);
			e_beam->tag = "UnFriendly";

			//Lazer Components Init
			std::unique_ptr<bls::SpriteComponent> component = CREATE_CLASS(SpriteComponent)
			component->m_texture = GET_RESOURCE(bls::Texture, "lazer.png", bls::g_renderer);
			e_beam->AddComponent(std::move(component));

			//Collision Component for Lazer
			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			e_beam->AddComponent(std::move(collisionComponent));

			e_beam->Initialize();
			m_scene->Add(std::move(e_beam));
			*/


		}


		bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forword * 1 * speed * dt;
		transform.position.x = bls::Wrap(transform.position.x, (float)bls::g_renderer.GetWidth());
		transform.position.y = bls::Wrap(transform.position.y, (float)bls::g_renderer.GetHeight());
	}

	void Enemy::OnCollisionEnter(GameObject* object)
	{
		if (object->tag == "Friendly" && !object->destroyed)
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
			bls::Transform transform{ { this->transform.position }, 0, 1 };
			auto emitter = std::make_unique<bls::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));

			m_curGame->m_enemiesKilled++;

			destroyed = true;
		}
	}

	void Enemy::Read(const rapidjson::Value& value)
	{
		GameObject::Read(value);
	}
}