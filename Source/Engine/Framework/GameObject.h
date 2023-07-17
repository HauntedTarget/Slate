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

		virtual void Update(float dt) = 0;
		virtual void Draw(bls::Renderer& renderer);

		class Scene* m_scene = nullptr;

	protected:
		bls::Transform m_transform;
		bls::Model m_model;
	};
}