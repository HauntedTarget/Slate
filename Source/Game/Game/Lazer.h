#pragma once

#include "Framework/GameObject.h"

class Lazer : public bls::GameObject
{

public:
	Lazer(float speed, const bls::Transform& transfrom, const bls::Model& model) :
		GameObject{ transfrom, model },
		m_speed{ speed }
	{}
	void Update(float dt) override;

private:
	float m_speed = 0;
};