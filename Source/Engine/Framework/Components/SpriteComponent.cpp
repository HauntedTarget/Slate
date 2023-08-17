#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/GameObject.h"
#include "Core/Json.h"
#include "Framework/Resource/ResourceManager.h"

namespace bls {

	CLASS_DEFINE(SpriteComponent);

	bool SpriteComponent::Initialize()
	{
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, textureName);
	}

}