#include "ModelRenderComponent.h"
#include "Framework/GameObject.h"

namespace bls{

	CLASS_DEFINE(ModelRenderComponent)

	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}
}
