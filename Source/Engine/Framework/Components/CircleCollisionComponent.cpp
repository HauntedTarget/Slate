#include "CircleCollisionComponent.h"
#include "Framework/GameObject.h"

namespace bls{

    CLASS_DEFINE(CircleCollisionComponent)

    void CircleCollisionComponent::Update(float dt)
    {

    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->m_transform.position.Distance(collision->GetOwner()->m_transform.position);
        float radius = m_radius + collision->m_radius;

        return (distance <= radius);
    }

}
