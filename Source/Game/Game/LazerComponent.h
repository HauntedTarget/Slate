#pragma once
#include "Framework/Components/Component.h"

namespace bls
{

	class LazerComponent : public Component
	{

	public:
		/*
		Lazer(float speed, const bls::Transform& transfrom) :
			GameObject{ transfrom },
			m_speed{ speed }
		{
			//Play Weapon Fire
			bls::g_audioSystem.PlayOneShot("shoot");
			lifespan = 1.5f;
		}
		*/

		bool Initialize();

		void Update(float dt) override;
		//void OnCollision(GameObject* object) override;
		void Read(const rapidJson::Value& value);

	private:
		float speed = 0;
	};

}