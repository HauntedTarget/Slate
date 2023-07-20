#include "Scene.h"

namespace bls{

	void Scene::Update(float dt)
	{
		/*for (auto& gameObjects : m_GameObjects)
		{
			gameObjects->Update(dt);
		}*/

		// Update and Remove Destroyed
		auto iter = m_GameObjects.begin();

		while (iter != m_GameObjects.end())
		{
			(*iter)->Update(dt);

			(iter->get()->m_destroyed) ? iter = m_GameObjects.erase(iter) : iter++;
		}

		//Check Collisions
		for (auto iter1 = m_GameObjects.begin(); iter1 != m_GameObjects.end(); iter1++) 
		{

			for (auto iter2 = std::next(iter1, 1); iter2 != m_GameObjects.end(); iter2++)
			{

				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				float combineRadius = (*iter1)->GetRadius() + (*iter2)->GetRadius();

				if (distance <= combineRadius) 
				{
					//OnCollision Caller
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}

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
