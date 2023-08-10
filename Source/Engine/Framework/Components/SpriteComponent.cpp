#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/GameObject.h"

namespace bls {

	void SpriteComponent::Update(float dt)
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}

}