#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace bls {

	class ModelRenderComponent : public RenderComponent {

	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

	public:
		shatr<Model> m_model;

	};
}