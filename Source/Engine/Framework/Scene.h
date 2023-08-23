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
		
		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<GameObject> gameObject);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const rapidjson::Value& value);

		template<typename T>
		T* GetGameObject();

		template<typename T = GameObject>
		T* GetGameObjectByName(const std::string name);

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

	template<typename T>
	inline T* Scene::GetGameObjectByName(const std::string name)
	{
		for (auto& gameObject : m_GameObjects)
		{
			if (gameObject->name == name) 
			{
				T* result = dynamic_cast<T*>(gameObject.get());
				if (result) {
					return result;
				}
			}
		}

		return nullptr;
	}

}