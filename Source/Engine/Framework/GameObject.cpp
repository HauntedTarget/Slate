#include "GameObject.h"
#include "Components/RenderComponent.h"

namespace bls
{
	CLASS_DEFINE(GameObject)

		GameObject::GameObject(const GameObject& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	bool GameObject::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void GameObject::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void GameObject::Update(float dt)
	{
		if (lifespan != -10.0f) 
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components)
		{
			component->Update(dt);
		}
	}

	void GameObject::Draw(bls::Renderer& renderer)
	{
		for (auto& component : components)
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
		components.push_back(std::move(component));
	}

	void GameObject::Read(const rapidjson::Value& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_OBJECT_C(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}
}