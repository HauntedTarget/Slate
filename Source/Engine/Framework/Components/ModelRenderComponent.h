#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace bls {

	class ModelRenderComponent : public RenderComponent {

	public:

		CLASS_DECLARE(ModelRenderComponent)

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		shatr<Model> m_model;

	};
}