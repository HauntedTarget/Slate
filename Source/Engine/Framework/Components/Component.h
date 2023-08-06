#pragma once

namespace bls {

	class Component {

	public:
		virtual void Update(float dt) = 0;

		friend class GameObject;

	protected:
		class GameObject* m_owner = nullptr;

	};
}