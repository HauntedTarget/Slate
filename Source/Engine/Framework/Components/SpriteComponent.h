#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace bls {

	class SpriteComponent : public RenderComponent {

	public:

		CLASS_DECLARE(SpriteComponent)

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }


	public:
		shatr<Texture> m_texture;

	};
}