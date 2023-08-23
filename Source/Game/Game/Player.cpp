#include "Player.h"
#include "FrameLastGame.h"
#include <Framework/Emitter.h>
#include "Input/InputSystem.h"
#include "Framework/Framework.h"

bool Player::Initialize()
{
	GameObject::Initialize();

	//cache off
	m_physicsComponent = GetComponent<bls::PhysicsComponent>();
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

void Player::Update(float dt)
{
	GameObject::Update(dt);

	//Timer Ticker
	noHitTime -= dt;

	//Movement Values
	float rotate = 0, thrust = 1;

	//Controls
		//Movement
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) thrust = 1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 1;
		//Shoot
	if ((bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !bls::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		|| (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_Z) && !bls::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_Z)))
	{
		auto weapon = INSTANTIATE(Lazer, "Beam");
		weapon->transform = { transform.position, transform.rotation, transform.scale * 0.5f };
		weapon->Initialize();
		weapon->tag = "Friendly";
		m_scene->Add(std::move(weapon));

		/*
		//Create Weapon
		bls::Transform transform{transform.position, transform.rotation, transform.scale * 0.5f};
		std::unique_ptr<bls::LazerComponent> p_beam = std::make_unique<bls::LazerComponent>( 400.0f, transform);
		p_beam->tag = "Friendly";

		//Lazer Components Init
		std::unique_ptr<bls::SpriteComponent> component = std::make_unique<bls::SpriteComponent>();
		component->m_texture = GET_RESOURCE(bls::Texture, "lazer.png", bls::g_renderer);
		p_beam->AddComponent(std::move(component));

		//Collision Component for Lazer
		auto collisionComponent = std::make_unique<bls::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		p_beam->AddComponent(std::move(collisionComponent));

		p_beam->Initialize();
		m_scene->Add(std::move(p_beam));
		*/
	}

	//Movement Updates
	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(transform.rotation);

	transform.rotation += rotate * m_turnRate * dt;
	//m_transform.position += forword * thrust * 1 * m_speed * dt;
	m_physicsComponent->ApplyForce(forword * thrust * 1 * speed * dt);

	transform.position.x = bls::Wrap(transform.position.x, (float)bls::g_renderer.GetWidth());
	transform.position.y = bls::Wrap(transform.position.y, (float)bls::g_renderer.GetHeight());
}

void Player::OnCollision(GameObject* object)
{

	if (object->tag == "UnFriendly" && !object->destroyed && noHitTime <= 0)
	{
		object->destroyed = true;

		noHitTime = 2;

		bls::EventManager::Instance().DispatchEvent("AddLife", -5);

		if (m_game->GetLife() <= 0)
		{
			//destroyed = true;

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
			data.color = bls::Color{ 1, 0, 0, 1 };
			bls::Transform transform{ { this->transform.position }, 0, 1 };
			auto emitter = std::make_unique<bls::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));

			bls::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);

			//dynamic_cast<bls::FrameLastGame*>(m_game)->SetState(bls::FrameLastGame::eState::GameOver);
		}
	}
}
