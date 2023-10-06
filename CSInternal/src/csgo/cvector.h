#pragma once
#include <numbers>
#include <cmath>

static float Deg2Rad(const float deg)
{
	return deg * (std::numbers::pi_v<float> / 180.f);
}

class CVector
{
public:
	CVector operator-(const CVector& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	CVector operator+(const CVector& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	CVector operator*(const float scale) const
	{
		return { x * scale, y * scale, z * scale };
	}

	// convert angles -> vector
	CVector ToVector() const
	{
		return {
			std::cos(Deg2Rad(x)) * std::cos(Deg2Rad(y)),
			std::cos(Deg2Rad(x)) * std::sin(Deg2Rad(y)),
			-std::sin(Deg2Rad(x))
		};
	}

public:
	float x{ };
	float y{ };
	float z{ };
};