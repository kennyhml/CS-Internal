#pragma once
#include <numbers>
#include <cmath>
#include <limits>

constexpr float Deg2Rad(float deg)
{
	return deg * (std::numbers::pi_v<float> / 180.f);
}

constexpr float Rad2Deg(float radians)
{
	return radians * (180.0f / std::numbers::pi_v<float>);
}




struct Vector2
{
	float x, y;

	constexpr Vector2(float x = 0.f, float y = 0.f)
		: x(x), y(y) { }

	bool IsZero() const
	{
		return !(std::fpclassify(this->x) || std::fpclassify(this->y));
	}
};

struct Vector3
{
	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };

	constexpr Vector3(float x = 0.f, float y = 0.f, float z = 0.f) :
		x(x), y(y), z(z) { }

	constexpr Vector3(const float* vec) :
		x(vec[0]), y(vec[1]), z(vec[2]) { }

	constexpr Vector3(const Vector2& vec) :
		x(vec.x), y(vec.y), z(0.0f) { }

	/**
	 * @brief Allows indexing into the float* representation of the vector.
	 */
	float operator[](int i)
	{
		return GetData()[i];
	}

	/**
	 * @brief Compares this vectors values to another vectors values.
	 */
	bool operator==(const Vector3& other)
	{
		return IsEqual(other);
	}

	bool operator!=(const Vector3& other)
	{
		return !IsEqual(other);
	}

	/**
	 * @brief Subtracts another vector from this vector.
	 */
	Vector3 operator-(const Vector3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	/**
	 * @brief Adds another vector to this vector.
	 */
	Vector3 operator+(const Vector3& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	/**
	 * @brief Multiplies another vector with this vector.
	 */
	Vector3 operator*(const float scale) const
	{
		return { x * scale, y * scale, z * scale };
	}

	Vector3 ToVector3() const
	{
		return {
			std::cos(Deg2Rad(x)) * std::cos(Deg2Rad(y)),
			std::cos(Deg2Rad(x)) * std::sin(Deg2Rad(y)),
			-std::sin(Deg2Rad(x))
		};
	}

	Vector3 ToAngle() const
	{
		return Vector3{ Rad2Deg(std::atan2(-z, std::hypot(x, y))),
					   Rad2Deg(std::atan2(y, x)),
					   0.0f };
	}

	/**
	 * @brief Returns whether the vector is valid.
	 */
	bool IsValid() const
	{
		return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
	}

	/**
	 * @brief Compares this vector to another vector.
	 */
	bool IsEqual(const Vector3& other, float margin = std::numeric_limits<float>::epsilon()) const
	{
		return (std::fabsf(this->x - other.x) < margin
			&& std::fabsf(this->y - other.y) < margin
			&& std::fabsf(this->z - other.z) < margin);
	}

	/**
	 * @brief Returns a float* representation of the vector.
	 */
	float* GetData()
	{
		return reinterpret_cast<float*>(this);
	}

	float Length() const
	{
		return std::sqrtf(DotProduct(*this));
	}

	float DotProduct(const Vector3& dot) const
	{
		return (this->x * dot.x + this->y * dot.y + this->z * dot.z);
	}

	float DistTo(const Vector3& other) const
	{
		return (*this - other).Length();
	}
};

class Vector4
{
public:
	constexpr Vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) :
		x(x), y(y), z(z), w(w) { }

public:
	float x, y, z, w;
};