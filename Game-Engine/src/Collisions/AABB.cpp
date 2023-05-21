#include "Engine_pch.h"

#include "AABB.h"
#include "Collisions/RaycastHit.h"
#include "Core/Geometry/Ray.h"
#include "Core/Math/Math.h"

namespace Engine {
bool AABB::Contains(const Math::Vector3& point) const {
  return (point.x >= Min.x && point.x <= Max.x) &&
         (point.y >= Min.y && point.y <= Max.y) &&
         (point.z >= Min.z && point.z <= Max.z);
}
bool AABB::Contains(const AABB& aabb) const {
  return Contains(aabb.min) && Contains(aabb.max);
}

bool AABB::Intersect(const AABB& other) const {
  return (Min.x <= other.Max.x && Max.x >= other.Min.x) &&
         (Min.y <= other.Max.y && Max.y >= other.Min.y) &&
         (Min.z <= other.Max.z && Max.z >= other.Min.z);
}
bool AABB::Intersect(const AABB* a, const AABB* b) {
  return (a->Min.x <= b->Max.x && a->Max.x >= b->Min.x) &&
         (a->Min.y <= b->Max.y && a->Max.y >= b->Min.y) &&
         (a->Min.z <= b->Max.z && a->Max.z >= b->Min.z);
}

void AABB::Expand(const float amount) {
  size += amount * Math::Vector3::one;
  extents = 0.5 * size;
  min = center - extents;
  max = center + extents;
}

void AABB::Encapsulate(const Math::Vector3& point) {
  Min.x = std::min(Min.x, point.x);
  Min.y = std::min(Min.y, point.y);
  Min.z = std::min(Min.z, point.z);
  Max.x = std::max(Max.x, point.x);
  Max.y = std::max(Max.y, point.y);
  Max.z = std::max(Max.z, point.z);
}
void AABB::Encapsulate(const AABB& other) {
  Min.x = std::min(Min.x, other.Min.x);
  Min.y = std::min(Min.y, other.Min.y);
  Min.z = std::min(Min.z, other.Min.z);
  Max.x = std::max(Max.x, other.Max.x);
  Max.y = std::max(Max.y, other.Max.y);
  Max.z = std::max(Max.z, other.Max.z);
}
AABB AABB::Encapsulate(const AABB& a, const AABB& b) {
  return AABBConstruct(Math::Vector3{std::min(a.Min.x, b.Min.x),
                                     std::min(a.Min.y, b.Min.y),
                                     std::min(a.Min.z, b.Min.z)},
                       Math::Vector3{std::max(a.Max.x, b.Max.x),
                                     std::max(a.Max.y, b.Max.y),
                                     std::max(a.Max.z, b.Max.z)});
}

bool AABB::Raycast(const Ray& ray, RaycastHit* const hitInfo,
                   float maxDistance) {
  float tmin = -INFINITY, tmax = maxDistance > 0 ? maxDistance : INFINITY;
  Math::Vector3 e = extents;
  Math::Vector3 o = ray.GetOrigin() - center;
  Math::Vector3 d = ray.GetDirection();
  Math::Vector3 invD = 1.0f / d;

  float t[6];
  for (int i = 0; i < 3; ++i) {
    t[2 * i] = -(e[i] + o[i]) * invD[i];
    t[2 * i + 1] = (e[i] - o[i]) * invD[i];
  }
  tmin =
      std::max({std::min(t[0], t[1]), std::min(t[2], t[3]),
                       std::min(t[4], t[5])});
  tmax =
      std::min({std::max(t[0], t[1]), std::max(t[2], t[3]),
                       std::max(t[4], t[5])});
  if (tmax < 0 || tmin > tmax) return false;
  if (tmin < 0) tmin = tmax;

  // TODO(Jacob) normal
  Math::Vector3 n;
  if (hitInfo) *hitInfo = std::move(RaycastHit{nullptr, tmin, o + d * tmin, n});
  return true;
}
} 