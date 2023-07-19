#pragma once
#include "Framework/GameObject.h"

class Enemy : public bls::GameObject
{

public:
	Enemy(float speed, float turnRate, const bls::Transform& transfrom, const bls::Model& model) :
		GameObject{ transfrom, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTimer = bls::randomf(2.0f, 4.0f);
	}
	void Update(float dt) override;

private:
	float m_speed = 0, m_turnRate = 0, m_fireTimer = 0;
};