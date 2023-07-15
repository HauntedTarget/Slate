#pragma once
#include "GameObject.h"

class Player : public GameObject
{

public:
	Player(float speed, float turnRate, const bls::Transform& transfrom, const bls::Model& model) :
		GameObject{ transfrom, model }, 
		m_speed{speed},
		m_turnRate{turnRate}
	{}
	void Update(float dt) override;

private:
	float m_speed = 0, m_turnRate = 0;
};