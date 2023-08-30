#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

#include <box2d/include/box2d/box2d.h>

namespace bls
{
	class Box2DPhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARE(Box2DPhysicsComponent)

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;

		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}