#pragma once
#include "Vector2.h"
#include "MatrixBy2.h"
#include "MatrixBy3.h"
#include "Core/Json.h"

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

		mat3 GetMatrix() const
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);

			return (mt * ms * mr);
		}

		void Read(const rapidjson::Value& value);
	};
}