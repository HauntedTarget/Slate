#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace bls {

	class PhysicsComponent : public Component {

	public:
		virtual void ApplyForce(const vec2& force) = 0;

	public:
		//Velocity & Acceleration
		vec2 m_vel, m_acel;
		//Mass & Force Dampening
		float m_mass = 1.0f, m_damping = 0;

	};
}