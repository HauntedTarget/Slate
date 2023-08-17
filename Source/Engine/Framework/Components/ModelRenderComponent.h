#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace bls {

	class ModelRenderComponent : public RenderComponent {

	public:

		CLASS_DECLARE(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		std::string modelName;
		shatr<Model> m_model;

	};
}