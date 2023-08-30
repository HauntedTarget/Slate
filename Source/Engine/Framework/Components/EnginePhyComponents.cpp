#include "EnginePhyComponents.h"
#include "Framework/GameObject.h"


namespace bls{

	CLASS_DEFINE(EnginePhyComponents)

	void EnginePhyComponents::Update(float dt)
	{
		m_owner->transform.position += m_vel * dt;
		m_vel *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhyComponents::ApplyForce(const vec2& force)
	{
		m_vel += force;
	}

	void EnginePhyComponents::ApplyTorque(float torque)
	{

	}

	void EnginePhyComponents::Read(const rapidjson::Value& value)
	{

	}
}
