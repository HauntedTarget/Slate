#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Framework/Components/Component.h"
#include "Framework/Object.h"
#include <memory>

namespace bls{
	class GameObject : public Object
	{
	public:
		GameObject() = default;
		GameObject(const bls::Transform& transform) :
			m_transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(bls::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		float GetRadius() { return (30.0f); }
		virtual void OnCollision(GameObject* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform m_transform;

		std::string m_tag;

		bool m_destroyed = false;

		//Can be used as a range for lazers/bullets
		float m_lifespan = -10.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

	};

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& comp : m_components)
		{
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}

		return nullptr;
	}
}