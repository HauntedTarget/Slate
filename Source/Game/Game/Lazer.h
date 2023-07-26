#pragma once

#include "Framework/GameObject.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

class Lazer : public bls::GameObject
{

public:
	Lazer(float speed, const bls::Transform& transfrom, std::shared_ptr<bls::Model> model) :
		GameObject{ transfrom, model },
		m_speed{ speed }
	{
		//Play Weapon Fire
		bls::g_audioSystem.PlayOneShot("shoot");
		m_lifespan = 1.5f;
	}
	void Update(float dt) override;
	void OnCollision(GameObject* object) override;

private:
	float m_speed = 0;
};