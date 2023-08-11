#include "FrameLastGame.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Enemy.h"
#include "Player.h"
#include <Framework/Emitter.h>
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/EnginePhyComponents.h"
#include "Framework/Components/ModelRenderComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"

namespace bls
{

	bool FrameLastGame::Init()
	{
		//Init Assets
		g_audioSystem.AddAudio("death", "explode.wav");
		g_audioSystem.AddAudio("shoot", "lazer.wav");

		g_audioSystem.AddAudio("music", "Bullet Hellz.wav");

		// Init Font
		m_font = bls::g_resources.Get<bls::Font>("Arcade.ttf", 24);

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
			m_wave = 0;
			m_life = 100;
			m_state = eState::StartLevel;
			g_audioSystem.PlayOneShot("music", true);
			break;

		case eState::StartLevel:
			m_scene->RemoveAll();
		{
			//Player Creation
			std::unique_ptr<Player> player = std::make_unique<Player>(100.0f, (float)DegreesToRadians(180), Transform(((g_renderer.GetHeight() / 2), (g_renderer.GetWidth() / 2)), 0, 1));
			player->m_tag = "Player";
			player->m_game = this;

			//Player Components Init:

				//Render Component for Player
			std::unique_ptr<bls::SpriteComponent> renderComponent = std::make_unique<bls::SpriteComponent>();
			renderComponent->m_texture = bls::g_resources.Get<bls::Texture>("Ship.png", bls::g_renderer);
			player->AddComponent(std::move(renderComponent));

				//Physics Component for Player
			auto phyComponent = std::make_unique<bls::EnginePhyComponents>();
			phyComponent->m_damping = 0.8f;
			player->AddComponent(std::move(phyComponent));

				//Collision Component for Player
			auto collisionComponent = std::make_unique<bls::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			player->Initialize();
			m_scene->Add(std::move(player));
		}
		m_wave++;
		m_waveSize = random(3 + m_wave, 7 + m_wave);
		m_enemiesIn = 0;
		m_enemiesKilled = 0;
		m_state = eState::Game;
		m_spawnTime = 2 - (0.001f * m_wave);
		if (m_spawnTime <= 0) m_spawnTime = 0.001f;
		m_life += 5;
		if (m_life >= 100)
		{
			m_life = 100;
		}
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
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(50.0f, (float)DegreesToRadians(180), Transform((random((float)g_renderer.GetWidth()), random((float)g_renderer.GetHeight())), randomf(360), 1), this);
				enemy->m_tag = "Enemy";
				enemy->m_game = this;
				//Enemy Components Init
				std::unique_ptr<bls::SpriteComponent> component = std::make_unique<bls::SpriteComponent>();
				component->m_texture = bls::g_resources.Get<bls::Texture>("enemy.png", bls::g_renderer);
				enemy->AddComponent(std::move(component));

				//Collision Component for Enemy
				auto collisionComponent = std::make_unique<bls::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				m_scene->Add(std::move(enemy));
			}

			//Detect Enemies Killed
			if (m_enemiesKilled >= m_waveSize) {
				m_fighting = false;
				m_state = eState::ClearBuffer;
			}

			break;

		case eState::Upgrading:

			if (bls::g_inputSystem.GetKeyDown(SDL_SCANCODE_RETURN))
			{
				m_fighting = true;
				m_state = eState::ClearBuffer;
			}
			break;

		case eState::ClearBuffer:
			m_scene->RemoveAll();
			if (m_fighting) {
				m_state = eState::StartLevel;
			}
			else {
				m_state = eState::Upgrading;
			}
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
			m_titleText->Draw(renderer, renderer.GetHeight()/2 + 50, 300);
		}
		else if(m_state == eState::GameOver) {

			m_titleText->Create(g_renderer, "GAME OVER", Color{ 0.5, 1, 0, 1 });
			m_titleText->Draw(renderer, renderer.GetHeight()/2 + 50, 300);
		}
		else if (m_state == eState::Upgrading) {

			m_titleText->Create(g_renderer, "Wave Complete", Color{ 0.5, 1, 0, 1 });
			m_titleText->Draw(renderer, renderer.GetHeight()/2 + 50, 300);
			m_titleText->Create(g_renderer, "(Enter to Continue)", Color{ 0.5, 1, 0, 1 });
			m_titleText->Draw(renderer, renderer.GetHeight()/2 + 50, 350);
			//(Space to Continue)
		}

		if (m_state != eState::Title && m_state != eState::GameOver && m_state != eState::Upgrading) {
			m_waveText->Draw(renderer, 20, 20);
		}
		m_scene->Draw(renderer);

	}
}