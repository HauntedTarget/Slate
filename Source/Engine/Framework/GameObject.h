#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Core/Memory.h"
#include "Framework/Components/Component.h"
#include <memory>

namespace bls{
	class GameObject
	{

	public:
		GameObject(const bls::Transform& transfrom, std::shared_ptr<Model> model) :
			m_transform{ transfrom },
			m_model{ model }
		{}

		GameObject(const bls::Transform& transform) :
			m_transform{ transform }
		{}


		virtual void Update(float dt);
		virtual void Draw(bls::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
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

		std::shared_ptr<Model> m_model;
	};
}