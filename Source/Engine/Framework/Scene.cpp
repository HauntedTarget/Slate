#include "Scene.h"

namespace bls{

	void Scene::Update(float dt)
	{
		for (auto* gameObjects : m_GameObjects)
		{
			gameObjects->Update(dt);
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto* gameObjects : m_GameObjects)
		{
			gameObjects->Draw(renderer);
		}
	}

	void Scene::Add(GameObject* object)
	{
		object->m_scene = this;
		m_GameObjects.push_back(object);
	}

	void Scene::Remove(GameObject* object)
	{
		m_GameObjects.remove(object);
	}

	void Scene::RemoveAll()
	{
		m_GameObjects.clear();
	}
}
