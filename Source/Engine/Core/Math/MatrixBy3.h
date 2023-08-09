#pragma once
#include "Vector3.h"
#include "Vector2.h"

namespace bls {

	class MatrixBy3
	{
	public:
		vec3 rows[3];
		// [row][column]
		// rows[0] = vec3{ 0, 0, 0 }
		// rows[1] = vec3{ 0, 0, 0 }
		// rows[2] = vec3{ 0, 0, 0 }

		MatrixBy3() = default;
		MatrixBy3(const vec3& row1, const vec3& row2, const vec3& row3)
		{
			rows[0] = row1;
			rows[1] = row2;
			rows[2] = row3;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec3 operator * (const vec3& v);
		MatrixBy3 operator * (const MatrixBy3& mx);

		static MatrixBy3 CreateScale(const vec2& scale);
		static MatrixBy3 CreateScale(float scale);
		static MatrixBy3 CreateRotation(float radians);

		static MatrixBy3 CreateIdentity();
	};

	inline MatrixBy3 MatrixBy3::CreateIdentity()
	{
		return
		{
			{1,0,0},
			{0,1,0},
			{0,0,1}

		};
	}

	inline vec3 MatrixBy3::operator*(const vec3& v)
	{
		vec3 result;

		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline MatrixBy3 MatrixBy3::operator*(const MatrixBy3& mx)
	{
		MatrixBy3 result;

		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline MatrixBy3 MatrixBy3::CreateScale(const vec2& scale)
	{
		MatrixBy3 mx = CreateIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline MatrixBy3 MatrixBy3::CreateScale(float scale)
	{
			MatrixBy3 mx = CreateIdentity();
			mx[0][0] = scale;
			mx[1][1] = scale;

			return mx;
	}

	inline MatrixBy3 MatrixBy3::CreateRotation(float radians)
	{
		MatrixBy3 mx = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		mx[0][0] = c;
		mx[0][1] = -s;
		mx[1][0] = s;
		mx[1][1] = c;

		return mx;
	}

	using mat3 = MatrixBy3;
}