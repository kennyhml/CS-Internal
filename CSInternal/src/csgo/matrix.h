#pragma once
#include "vector.h"

struct CMatrix3x4
{
	constexpr float* operator[](size_t index) noexcept
	{
		return data[index];
	}

	constexpr Vector3 Origin() noexcept
	{
		return { data[0][3], data[1][3], data[2][3] };
	}

	float data[3][4];
};

struct CMatrix4x4
{
	float data[4][4];
};