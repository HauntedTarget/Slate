#pragma once
#include "Vector2.h"

namespace bls{

	class MatrixBy2
	{
	public:
		vec2 rows[2];
		// [row][column]
		// rows[0] = vec2{ 0, 0 }
		// rows[1] = vec2{ 0, 0 }

		MatrixBy2() = default;
		MatrixBy2(const vec2& row1, const vec2& row2) 
		{
			rows[0] = row1;
			rows[1] = row2;
		}

		vec2  operator [] (size_t index) const { return rows[index]; }
		vec2& operator [] (size_t index) { return rows[index]; }

		vec2 operator * (const vec2& v);
		MatrixBy2 operator * (const MatrixBy2& mx);

		static MatrixBy2 CreateScale(const vec2& scale);
		static MatrixBy2 CreateScale(float scale);
		static MatrixBy2 CreateRotation(float radians);

		static MatrixBy2 CreateIdentity();
	};

	inline MatrixBy2 MatrixBy2::CreateIdentity() 
	{
		return
		{
			{1,0},
			{0,1}
		};
	}

	inline vec2 MatrixBy2::operator*(const vec2& v)
	{
		vec2 result;

		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline MatrixBy2 MatrixBy2::operator*(const MatrixBy2& mx)
	{
		MatrixBy2 result;

		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline MatrixBy2 MatrixBy2::CreateScale(const vec2& scale)
	{
		return
		{
			{scale.x, 0.0f},
			{0.0f, scale.y}
		};
	}

	inline MatrixBy2 MatrixBy2::CreateScale(float scale)
	{
		return
		{
			{scale, 0.0f},
			{0.0f, scale}
		};
	}

	inline MatrixBy2 MatrixBy2::CreateRotation(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return
		{
			{c, -s},
			{s, c}
		};
	}

	using mat2 = MatrixBy2;
}