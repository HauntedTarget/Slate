#pragma once
#include "Vector2.h"
#include "MatrixBy2.h"

namespace bls
{
	class Transform
	{

	public:
		vec2 position;
		float rotation = 0, scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		mat2 GetMatrix() const
		{
			mat2 ms = mat2::CreateScale(scale);
			mat2 mr = mat2::CreateRotation(rotation);

			return ms * mr;
		}
	};
}