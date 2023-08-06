#include "GameObject.h"
#include "Components/RenderComponent.h"

namespace bls
{
	void GameObject::Update(float dt)
	{
		if (m_lifespan != -10.0f) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
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
}