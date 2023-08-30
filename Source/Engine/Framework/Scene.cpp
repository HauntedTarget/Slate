#include "Scene.h"
#include "Audio/AudioSystem.h"
#include "Components/CollisionComponent.h"

namespace bls{

	bool Scene::Initialize()
	{
		for (auto& GameObject : m_GameObjects) GameObject->Initialize();

		return true;
	}

	void Scene::Update(float dt)
	{
		// Update and Remove Destroyed
		auto iter = m_GameObjects.begin();

		while (iter != m_GameObjects.end())
		{
			if ((*iter)->active) (*iter)->Update(dt);

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
					//OnCollisionEnter Caller
					(*iter1)->OnCollisionEnter(iter2->get());
					(*iter2)->OnCollisionEnter(iter1->get());
				}

			}

		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& gameObjects : m_GameObjects)
		{
			if (gameObjects->active) gameObjects->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<GameObject> gameObject)
	{
		gameObject->m_scene = this;
		m_GameObjects.push_back(std::move(gameObject));
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_GameObjects.begin();

		while (iter != m_GameObjects.end())
		{

			if (!(*iter)->persistent || force)
			{
				iter = m_GameObjects.erase(iter);
			}
			else iter++;
		}
	}

	bool Scene::Load(const std::string& filename)
	{
		rapidjson::Document document;
		if (!Json::Load(filename, document))
		{
			ERROR_LOG("Could not load scene file: " << filename);
		}

		Read(document);

		return false;
	}

	void Scene::Read(const rapidjson::Value& value) 
	{
		if (HAS_DATA(value, gameobjects) && GET_DATA(value, gameobjects).IsArray())
		{
			for (auto& gameObjectValue : GET_DATA(value, gameobjects).GetArray())
			{
				std::string type;
				READ_DATA(gameObjectValue, type);

				auto gameObject = Factory::Instance().Create<GameObject>(type);
				if (gameObject)
				{
					gameObject->Read(gameObjectValue);
					INFO_LOG("Read ->" << gameObject->name);

					if (gameObject->prototype)
					{
						std::string name = gameObject->name;
						Factory::Instance().RegisterP(name, std::move(gameObject));
					}
					else
					{
						Add(std::move(gameObject));
					}
				}
			}
		}
	}
}
