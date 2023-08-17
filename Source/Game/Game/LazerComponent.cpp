#include "LazerComponent.h"
#include "Framework/Framework.h"

namespace bls
{
	bool LazerComponent::Initialize()
	{
		auto collisionComponent = Component::m_owner->GetComponent<bls::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = Component::m_owner->GetComponent<bls::RenderComponent>();
			if (renderComponent)
			{
				float scale = Component::m_owner->transform.scale;
				collisionComponent->m_radius = Component::m_owner->GetComponent<bls::RenderComponent>()->GetRadius() * scale;
			}
		}

		return true;
	}

	void LazerComponent::Update(float dt)
	{
		/*lifespan -= dt;
		if (transform.position.x < -25 || transform.position.x > bls::g_renderer.GetWidth() + 25 ||
			transform.position.y < -25 || transform.position.y > bls::g_renderer.GetHeight() + 25)
		{
			destroyed = true;
		}
		if (lifespan <= 0)
		{
			destroyed = true;
		}*/

		bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(Component::m_owner->transform.rotation);
		Component::m_owner->transform.position += forword * 1 * speed * dt;
	}

	void LazerComponent::Read(const rapidJson::Value& value)
	{
		READ_DATA(value, speed);
	}

	/*void Lazer::OnCollision(GameObject* object)
	{
		if (!m_scene->GetGameObject<Lazer>() && !object->destroyed)
		{
			destroyed = true;
		}
	}*/
}
