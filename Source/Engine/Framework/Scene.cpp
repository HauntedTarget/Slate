#include "Scene.h"

namespace bls{

	void Scene::Update(float dt)
	{
		/*for (auto& gameObjects : m_GameObjects)
		{
			gameObjects->Update(dt);
		}*/

		// Remove Destroyed
		auto iter = m_GameObjects.begin();

		while (iter != m_GameObjects.end())
		{
			(*iter)->Update(dt);
			if (iter->get()->m_destroyed) 
			{
				iter = m_GameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& gameObjects : m_GameObjects)
		{
			gameObjects->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<GameObject> gameObject)
	{
		gameObject->m_scene = this;
		m_GameObjects.push_back(std::move(gameObject));
	}

	void Scene::RemoveAll()
	{
		m_GameObjects.clear();
	}
}
