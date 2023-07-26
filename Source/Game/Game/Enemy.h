#pragma once
#include "Framework/GameObject.h"
#include "Lazer.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "FrameLastGame.h"

class Enemy : public bls::GameObject
{

public:
	Enemy(float speed, float turnRate, const bls::Transform& transfrom, std::shared_ptr<bls::Model> model, bls::FrameLastGame* curGame) :
		GameObject{ transfrom, model },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_curGame { curGame }
	{
		m_fireTimer = bls::randomf(2.0f, 4.0f);
	}
	void Update(float dt) override;
	void OnCollision(GameObject* object) override;

private:
	float m_speed = 0, m_turnRate = 0, m_fireTimer = 0;
	bls::FrameLastGame* m_curGame;

};