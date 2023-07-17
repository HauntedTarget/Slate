#pragma once

#include "GameObject.h"
#include <list>

namespace bls
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(GameObject* object);
		void Remove(GameObject* object);
		void RemoveAll();

		friend class GameObject;

	private:
		std::list<GameObject*> m_GameObjects;

	};

}