#include "Lazer.h"
#include "Framework/Framework.h"

namespace bls
{
	bool Lazer::Initialize()
	{
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

	void Lazer::Update(float dt)
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

		bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forword * 1 * speed * dt;
	}

	void Lazer::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
	}

	void Lazer::OnCollision(GameObject* object)
	{
		if (!m_scene->GetGameObject<Lazer>() && !object->destroyed)
		{
			destroyed = true;
		}
	}
}
