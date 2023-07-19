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

		void Add(std::unique_ptr<GameObject> gameObject);
		void RemoveAll();

		template<typename T>
		T* GetGameObject();

		friend class GameObject;

	private:
		std::list <std::unique_ptr<GameObject>> m_GameObjects;

	};

	template<typename T>
	inline T* Scene::GetGameObject()
	{
		for (auto& gameObject : m_GameObjects)
		{
			T* result = dynamic_cast<T*>(gameObject.get());
			if (result) {
				return result;
			}
		}

		return nullptr;
	}

}