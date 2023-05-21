#pragma once
#define NOMINMAX
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector2.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <cmath>
namespace Engine::Math
{
#define M_PI 3.14159265358979323846
	const float PI = static_cast<float>(M_PI);
	const float PI_HALF = 0.5f * PI;
	const float EPSILON = FLT_EPSILON;
	const float DEG2RAD = PI / 180.f;
	const float RAD2DEG = 180.f * static_cast<float>(M_PI);

	int Sign(double x)
	{
		return abs(x) / x;
	}

	bool fuzzyEquals(double a, double b) {
		return std::abs(a - b) < EPSILON;
	}
}
