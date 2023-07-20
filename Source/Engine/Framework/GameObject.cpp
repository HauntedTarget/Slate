#include "GameObject.h"

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
		m_model->Draw(renderer, m_transform);
	}
}