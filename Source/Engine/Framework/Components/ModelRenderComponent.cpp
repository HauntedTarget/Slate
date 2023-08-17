#include "ModelRenderComponent.h"
#include "Framework/GameObject.h"
#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"

namespace bls{

	CLASS_DEFINE(ModelRenderComponent);

	bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty() ) m_model = GET_RESOURCE(Model, modelName, g_renderer);

		return true;
	}

	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, modelName);
	}
}
