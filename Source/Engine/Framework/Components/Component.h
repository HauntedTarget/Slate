#pragma once
#include "Framework/Object.h"

namespace bls {

	class Component : public Object {

	public:
		virtual void Update(float dt) = 0;

		friend class GameObject;

		GameObject* GetOwner() { return m_owner; }

	protected:
		class GameObject* m_owner = nullptr;

	};
}