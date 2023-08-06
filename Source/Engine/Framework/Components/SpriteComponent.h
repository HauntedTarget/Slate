#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace bls {

	class SpriteComponent : public RenderComponent {

	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

	public:
		shatr<Texture> m_texture;

	};
}