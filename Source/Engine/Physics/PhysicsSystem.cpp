#include "PhysicsSystem.h"
#include <box2d/include/box2d/box2d.h>

namespace bls
{
	bool PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);
		return true;
	}
	void PhysicsSystem::Update(float dt)
	{
		//
	}
	
	b2Body* PhysicsSystem::CreateBody(const vec2& position, float angle, const RigidBodyData& data)
	{
		Vector2 worldPosition = ScreenToWorld(position);

		b2BodyDef bodyDef;
		bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = VEC2_TO_B2VEC2(worldPosition);
		bodyDef.angle = angle;
		bodyDef.fixedRotation = data.constrainAngle;
		b2Body* body = m_world->CreateBody(&bodyDef);

		return body;
	}

	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		m_world->DestroyBody(body);
	}

	void PhysicsSystem::SetCollisionBox(b2Body* body, const CollisionData& data, class GameObject* object)
	{
		b2PolygonShape shape;
		Vector2 worldSize = ScreenToWorld(data.size * 0.5f);
		shape.SetAsBox(worldSize.x, worldSize.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isTrigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(object);

		body->CreateFixture(&fixtureDef);
	}

	void PhysicsSystem::SetCollisionBoxStatic(b2Body* body, const CollisionData& data, GameObject* object)
	{
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);

		b2Vec2 vs[4] =
		{
			{ -worldSize.x, -worldSize.y },
			{  worldSize.x, -worldSize.y },
			{  worldSize.x,  worldSize.y },
			{ -worldSize.x,  worldSize.y },
		};

		b2ChainShape shape;
		shape.CreateLoop(vs, 4);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isTrigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(object);

		body->CreateFixture(&fixtureDef);
	}
}