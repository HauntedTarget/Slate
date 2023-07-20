#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Core/Memory.h"

#include <memory>

namespace bls{
	class GameObject
	{

	public:
		GameObject(const bls::Transform& transfrom, std::shared_ptr<Model> model) :
			m_transform{ transfrom },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(bls::Renderer& renderer);

		float GetRadius() { return m_model->GetRadius() * m_transform.scale; }
		virtual void OnCollision(GameObject* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		Transform m_transform;

		std::string m_tag;

		bool m_destroyed = false;

	protected:
		//Can be used as a range for lazers/bullets
		float m_lifespan = -10.0f;

		std::shared_ptr<Model> m_model;
	};
}