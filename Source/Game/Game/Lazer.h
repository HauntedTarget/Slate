#pragma once
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"

namespace bls
{

	class Lazer : public GameObject
	{

	public:
		CLASS_DECLARE(Lazer)

		//Lazer(float speed, const bls::Transform& transfrom) :
		//	GameObject{ transfrom },
		//	speed{ speed }
		//{
		//	//Play Weapon Fire
		//	bls::g_audioSystem.PlayOneShot("shoot");
		//	lifespan = 1.5f;
		//}
		

		bool Initialize();

		void Update(float dt) override;
		void OnCollisionEnter(GameObject* object) override;
		//void Read(const rapidjson::Value& value);

	private:
		float speed = 0;
		bls::PhysicsComponent* m_physicsComponent = nullptr;
	};

}