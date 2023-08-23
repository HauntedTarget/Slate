#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Framework/Event/EventManager.h"

namespace bls
{
	class FrameLastGame : public bls::Game, bls::IEventListener
	{

	public:
		enum class eState
		{
			Title = 0,
			StartGame = 1,
			StartLevel = 2,
			Game = 3,
			Upgrading = 4,
			ClearBuffer = 5,
			GameOver = 6
		};

	public:
		// Inherited via Game
		virtual bool Init() override;

		virtual void Shutdown() override;

		virtual void Update(float dt) override;

		virtual void Draw(Renderer& renderer) override;

		void SetState(eState state) { m_state = state; }

		void AddLife(const bls::Event& event);

		void OnPlayerDead(const bls::Event& event);

		int m_enemiesKilled = 0;
		bool m_fighting = true;

	private:
		eState m_state = eState::Title;
		float m_spawnTimer = 0, m_spawnTime = 0;
		int m_waveSize = 0, m_enemiesIn = 0;

		std::shared_ptr<Font> m_font;
		std::unique_ptr<Text> m_waveText;
		std::unique_ptr<Text> m_titleText;

	};
}