#pragma once
#include "Framework/GameObject.h"
#include "Lazer.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

class Player : public bls::GameObject
{

public:
	Player(float speed, float turnRate, const bls::Transform& transfrom, std::shared_ptr<bls::Model> model) :
		GameObject{ transfrom, model }, 
		m_speed{speed},
		m_turnRate{turnRate}
	{}
	void Update(float dt) override;
	void OnCollision(GameObject* object) override;

	float noHitTime = 0;

private:
	float m_speed = 0, m_turnRate = 0;
};