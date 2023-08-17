#include "ModelRenderComponent.h"
#include "Framework/GameObject.h"
#include "Framework/Resource/ResourceManager.h"

namespace bls{

	CLASS_DEFINE(ModelRenderComponent);

	bool ModelRenderComponent::Initialize()
	{
		m_model = GET_RESOURCE(Model, md, g_renderer);

		return true;
	}

	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::Read(const rapidJson::Value& value)
	{
		READ_DATA(value, textureName);
	}
}
