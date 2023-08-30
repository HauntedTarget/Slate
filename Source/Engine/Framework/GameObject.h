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
		CLASS_DECLARE(GameObject)

		GameObject() = default;
		GameObject(const bls::Transform& transform) :
			transform{ transform }
		{}
		GameObject(const GameObject& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(bls::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		virtual void OnCollisionEnter(GameObject* other) {}

		virtual void OnCollisionExit(GameObject* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform transform;

		std::string tag;

		bool destroyed = false, persistent = false, prototype = false;

		//Can be used as a range for lazers/bullets
		float lifespan = -10.0f;

	protected:
		std::vector<std::unique_ptr<Component>> components;

	};

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& comp : components)
		{
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}

		return nullptr;
	}
}