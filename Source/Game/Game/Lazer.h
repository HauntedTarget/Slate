#pragma once

#include "Framework/GameObject.h"
#include "Audio/AudioSystem.h"

class Lazer : public bls::GameObject
{

public:
	Lazer(float speed, const bls::Transform& transfrom, const bls::Model& model) :
		GameObject{ transfrom, model },
		m_speed{ speed }
	{
		//Play Weapon Fire
		bls::g_audioSystem.PlayOneShot("shoot");
	}
	void Update(float dt) override;

private:
	float m_speed = 0;
};