#include "FrameLastGame.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ModelManager.h"
#include "Enemy.h"
#include "Player.h"
#include <Framework/Emitter.h>

namespace bls
{

	bool FrameLastGame::Init()
	{
		//Init Assets
		g_audioSystem.AddAudio("death", "explode.wav");
		g_audioSystem.AddAudio("shoot", "lazer.wav");

		// Init Font
		m_font = std::make_shared<Font>("Arcade.ttf", 24);

		//Create Text Object
		m_titleText = std::make_unique<Text>(m_font);
		m_titleText->Create(g_renderer, "FrameLast", Color{ 0.5, 1, 0, 1 });

		m_waveText = std::make_unique<Text>(m_font);
		m_waveText->Create(g_renderer, "FrameLast", Color{ 0.5, 1, 0, 1 });

		//Scene Init
		m_scene = std::make_unique <bls::Scene>();

		return false;
	}

	void FrameLastGame::Shutdown()
	{
	}

	void FrameLastGame::Update(float dt)
	{

		switch (m_state)
		{
		case eState::Title:
			if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) 
			{
				m_state = eState::StartGame;
			}
			break;

		case eState::StartGame:
			m_wave = 1;
			m_life = 100;
			m_state = eState::StartLevel;
			break;

		case eState::StartLevel:
			m_scene->RemoveAll();
		{
			//Player Creation
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, (float)DegreesToRadians(180), Transform((400, 300), 0, 3), g_modelLib.Get("Player.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			m_scene->Add(std::move(player));
		}
		m_waveSize = random(1, 5);
		m_enemiesIn = 0;
		m_state = eState::Game;
		m_spawnTime = 3;
			break;

		case eState::Game:
			//Timer Ticker
			m_spawnTimer += dt;

			if (m_spawnTimer > m_spawnTime && m_enemiesIn < m_waveSize) {
				//Timer Reset
				m_spawnTimer = 0;
				//Wave Size Check
				m_enemiesIn++;
				//Spawn Enemy
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(50.0f, (float)DegreesToRadians(180), Transform((random((float)g_renderer.GetWidth()), random((float)g_renderer.GetHeight())), randomf(360), 5), g_modelLib.Get("Enemy.txt"));
				enemy->m_tag = "Enemy";
				enemy->m_game = this;
				m_scene->Add(std::move(enemy));
			}

			break;

		case eState::Upgrading:
			break;

		case eState::ClearBuffer:
			break;

		case eState::GameOver:
			m_scene->RemoveAll();
			break;

		default:
			break;
		}
		//Info Board Thing
		m_waveText->Create(g_renderer, "Wave: " + std::to_string(m_wave) + " Life: " + std::to_string((int)m_life), {1,1,1,1});
		m_scene->Update(dt);

	}

	void FrameLastGame::Draw(Renderer& renderer)
	{
		if (m_state == eState::Title) 
		{
			m_titleText->Create(g_renderer, "FrameLast", Color{ 0.5, 1, 0, 1 });
			m_titleText->Draw(renderer, 400, 300);
		}
		else if(m_state == eState::GameOver) {

			m_titleText->Create(g_renderer, "GAME OVER", Color{ 0.5, 1, 0, 1 });
			m_titleText->Draw(renderer, 400, 300);
		}

		if (m_state != eState::Title && m_state != eState::GameOver) {
			m_waveText->Draw(renderer, 40, 20);
		}
		m_scene->Draw(renderer);

	}
}