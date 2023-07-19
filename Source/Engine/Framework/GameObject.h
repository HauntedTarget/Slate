#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

namespace bls{
	class GameObject
	{

	public:
		GameObject(const bls::Transform& transfrom, const bls::Model& model) :
			m_transform{ transfrom },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(bls::Renderer& renderer);

		class Scene* m_scene = nullptr;
		friend class Scene;

		bls::Transform m_transform;

	protected:
		bool m_destroyed = false;
		//Can be used as a range for lazers/bullets
		float m_lifespan = -10.0f;

		bls::Model m_model;
	};
}