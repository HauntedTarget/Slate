#include "Lazer.h"
#include "Framework/Framework.h"

bool Lazer::Initialize()
{
	GameObject::Initialize();

	auto collisionComponent = GetComponent<bls::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<bls::RenderComponent>();
		if (renderComponent)
		{
			float scale = m_transform.scale;
			collisionComponent->m_radius = GetComponent<bls::RenderComponent>()->GetRadius() * scale;
		}
	}

	return true;
}

void Lazer::Update(float dt)
{
	m_lifespan -= dt;
	if (m_transform.position.x < -25 || m_transform.position.x > bls::g_renderer.GetWidth() + 25 ||
		m_transform.position.y < -25 || m_transform.position.y > bls::g_renderer.GetHeight() + 25)
	{
		m_destroyed = true;
	}
	if (m_lifespan <= 0)
	{
		m_destroyed = true;
	}
	GameObject::Update(dt);

	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forword * 1 * m_speed * dt;
}

void Lazer::OnCollision(GameObject* object)
{
	if (!m_scene->GetGameObject<Lazer>() && !object->m_destroyed)
	{
		m_destroyed = true;
	}
}
