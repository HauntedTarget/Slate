#pragma once
#include "Framework/GameObject.h"
#include "Lazer.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Components/PhysicsComponent.h"

namespace bls{
	class Player : public bls::GameObject
	{

	public:
		CLASS_DECLARE(Player)

		//Player(float speed, float turnRate, const bls::Transform& transfrom) :
		//	GameObject{ transfrom },
		//	speed{ speed },
		//	m_turnRate{ turnRate }
		//{}

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(GameObject* object) override;

		float noHitTime = 0;

	private:
		float speed = 0, m_turnRate = 0;

		bls::PhysicsComponent* m_physicsComponent = nullptr;
	};
}