#include "GameObject.h"
#include "Components/RenderComponent.h"

namespace bls
{
	CLASS_DEFINE(GameObject)

	bool GameObject::Initialize()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}

		return true;
	}

	void GameObject::OnDestroy()
	{
		for (auto& component : m_components)
		{
			component->OnDestroy();
		}
	}

	void GameObject::Update(float dt)
	{
		if (m_lifespan != -10.0f) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components)
		{
			component->Update(dt);
		}
	}

	void GameObject::Draw(bls::Renderer& renderer)
	{
		for (auto& component : m_components)
		{
			RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}
	}

	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

	bool GameObject::Read(const rapidjson::Value& value)
	{


		return true;
	}
}