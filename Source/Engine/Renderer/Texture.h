#pragma once
#include "Core/Vector2.h"
#include "Framework/Resource/Resource.h"

struct SDL_Texture;
namespace bls
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);
		vec2 GetSize();

		// Inherited via Resource
		virtual bool Create(std::string filename, ...) override;

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}