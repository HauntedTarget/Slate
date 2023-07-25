#pragma once
#include <memory>

namespace bls 
{
	class Scene;
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() const { return m_wave; }
		void SurvWave(int waves) {m_wave += waves; }

		int GetLife() const { return m_life; }
		void SetLife(int lifeGained) { m_life += lifeGained; }

	protected:
		std::unique_ptr<Scene> m_scene;

		int m_wave = 0, m_life = 0;

	private:

	};

}