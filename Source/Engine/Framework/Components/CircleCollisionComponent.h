#pragma once
#include "CollisionComponent.h"

namespace bls {

	class CircleCollisionComponent : public CollisionComponent {

	public:

		CLASS_DECLARE(CircleCollisionComponent)

		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComponent* collision) override;

	};
}