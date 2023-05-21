#define NOMINMAX
#include "Engine_pch.h"
#include "Math.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"

namespace Engine::Math {

const Vector3 Vector3::zero = Vector3();
const Vector3 Vector3::one = Vector3(1.f);
const Vector3 Vector3::up = Vector3(0.f, 1.f, 0.f);
const Vector3 Vector3::right = Vector3(-1.f, 0.f, 0.f);
const Vector3 Vector3::forward = Vector3(0.f, 0.f, 1.f);
const Vector3 Vector3::down = Vector3(0.f, -1.f, 0.f);
const Vector3 Vector3::left = Vector3(1.f, 0.f, 0.f);
const Vector3 Vector3::back = Vector3(0.f, 0.f, -1.f);


Vector3::Vector3(const Vector2& inVector, float inZ)
    : x{inVector.x}, y{inVector.y}, z{inZ} {}

Vector3::operator class Vector2() { return Vector2(x, y); }

float Vector3::operator[](int i) const {
  if (i < 0 || i > ELEMENT_COUNT - 1)
    throw std::out_of_range{"Vector3::[] => Index access out of range."};
  return xyz[i];
}
float& Vector3::operator[](int i) {
  if (i < 0 || i > ELEMENT_COUNT - 1)
    throw std::out_of_range{"Vector3::[] => Index access out of range."};
  return xyz[i];
}

float Vector3::Magnitude() const { return sqrtf(SqrMagnitude()); }
float Vector3::SqrMagnitude() const { return x * x + y * y + z * z; }
Vector3 Vector3::Normalized() const {
  float length{Magnitude()};
  return Vector3(x / length, y / length, z / length);
}
void Vector3::Normalize() noexcept {
  float length{Magnitude()};
  x /= length;
  y /= length;
  z /= length;
}

std::string Vector3::ToString() const {
  std::ostringstream oss;
  oss.precision(3);
  oss << std::fixed;
  oss << "(" << x << ", " << y << ", " << z << ")";
  return oss.str();
}

float Vector3::Max() const { return std::max({x, y, z}); }
float Vector3::Min() const { return std::min({x, y, z}); }

bool Vector3::FuzzyEqual(const Vector3& lhs, const Vector3& rhs) {
  return abs(lhs.x - rhs.x) < EPSILON &&
         abs(lhs.y - rhs.y) < EPSILON &&
         abs(lhs.z - rhs.z) < EPSILON;
}
float Vector3::Dot(const Vector3& lhs, const Vector3& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs) {
  return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, -lhs.x * rhs.z + lhs.z * rhs.x,
                 lhs.x * rhs.y - lhs.y * rhs.x);
}
Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float time) {
  return start * (1.f - time) + end * time;
}
float Vector3::Distance(const Vector3& start, const Vector3& end) {
  return (start - end).Magnitude();
}
Vector3 Vector3::Project(const Vector3& inVector, const Vector3& onNormal) {
  return onNormal.Normalized() * Dot(inVector, onNormal);
}
Vector3 Vector3::Reflect(const Vector3& inVector, const Vector3& inNormal) {
  Vector3 normal{inNormal.Normalized()};
  return inVector - normal * Dot(inVector, normal) * 2.f;
}
Vector3 Vector3::Scale(const Vector3& a, const Vector3& b) {
  return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::ReverseScale(const Vector3& a, const Vector3& b) {
  return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vector3 Vector3::Slerp(const Vector3& start, const Vector3& end, float time) {
  float dot = Dot(start, end);
  dot = dot < -1.f ? -1.f : (dot > 1.f ? 1.f : dot);
  float theta = acosf(dot) * time;
  Vector3 relativeVector = end - start * dot;
  return start * cosf(theta) + relativeVector * sinf(theta);
}
Vector3 Vector3::FromString(const std::string_view str) {
  Vector3 vec;
  char c;
  std::istringstream is(str.data());
  (is >> std::skipws) >> c >> vec.x >> c >> vec.y >> c >> vec.z;

  return vec;
}

float Vector3::AngleDeg(const Vector3& a, const Vector3& b) {
  return AngleRad(a, b) * RAD2DEG;
}

float Vector3::AngleRad(const Vector3& a, const Vector3& b) {
  return acos(Dot(a, b) / (a.Magnitude() * b.Magnitude()));
}
}  // namespace Engine::Math
