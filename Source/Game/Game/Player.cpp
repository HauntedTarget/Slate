#include "Player.h"
#include "FrameLastGame.h"
#include "Renderer/ModelManager.h"

void Player::Update(float dt)
{
	GameObject::Update(dt);

	//Movement Values
	float rotate = 0, scale = 10, thrust = 0;

	//Controls
		//Movement
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) thrust = 1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
	if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) || bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 1;
		//Shoot
	if ((bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !bls::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		|| (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_Z) && !bls::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_Z)))
	{
		//Create Weapon
		bls::Transform transform{m_transform.position, m_transform.rotation, m_transform.scale * 0.5f};
		std::unique_ptr<Lazer> beam = std::make_unique<Lazer>( 400.0f, transform, bls::g_modelLib.Get("Lazer.txt"));
		beam->m_tag = "Friendly";
		m_scene->Add(std::move(beam));
	}

	//Movement Updates
	bls::vec2 forword = bls::vec2{ 0,-1 }.Rotate(m_transform.rotation);

	m_transform.rotation += rotate * m_turnRate * dt;
	m_transform.scale = scale;
	m_transform.position += forword * thrust * m_speed * dt;
	m_transform.position.x = bls::Wrap(m_transform.position.x, (float)bls::g_renderer.GetWidth());
	m_transform.position.y = bls::Wrap(m_transform.position.y, (float)bls::g_renderer.GetHeight());
}

void Player::OnCollision(GameObject* object)
{
	//Player* p = dynamic_cast<Player>(other)

	if (object->m_tag == "UnFriendly" && !object->m_destroyed)
	{
		m_game->SetLife(m_game->GetLife() - 5);

		if (m_game->GetLife() <= 0)
		{
			m_destroyed = true;
			dynamic_cast<bls::FrameLastGame*>(m_game)->SetState(bls::FrameLastGame::eState::GameOver);
		}

		object->m_destroyed = true;
	}
}
