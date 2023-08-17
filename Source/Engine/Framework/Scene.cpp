#include "Scene.h"
#include "Audio/AudioSystem.h"
#include "Components/CollisionComponent.h"

namespace bls{

	void Scene::Update(float dt)
	{
		// Update and Remove Destroyed
		auto iter = m_GameObjects.begin();

		while (iter != m_GameObjects.end())
		{
			(*iter)->Update(dt);

			if (iter->get()->destroyed)
			{
				if (iter->get()->tag == "Player" || iter->get()->tag == "Enemy") bls::g_audioSystem.PlayOneShot("death");
				iter = m_GameObjects.erase(iter);
			}
			else iter++;
		}

		//Check Collisions
		for (auto iter1 = m_GameObjects.begin(); iter1 != m_GameObjects.end(); iter1++) 
		{

			for (auto iter2 = std::next(iter1, 1); iter2 != m_GameObjects.end(); iter2++)
			{

				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if (!collision1 || !collision2) {
					continue;
				}

				if (collision1->CheckCollision(collision2)) 
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
