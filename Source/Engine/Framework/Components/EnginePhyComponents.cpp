#include "EnginePhyComponents.h"
#include "Framework/GameObject.h"


namespace bls{

	void EnginePhyComponents::Update(float dt)
	{
		m_owner->m_transform.position += m_vel * dt;
		m_vel *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhyComponents::ApplyForce(const vec2& force)
	{
		m_vel += force;
	}
}
