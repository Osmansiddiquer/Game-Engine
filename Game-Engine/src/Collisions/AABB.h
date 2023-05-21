#pragma once
#include "Core/Math/Vector3.h"

namespace Engine {
class AABB {
 private:
  Math::Vector3 center, size, extents, min, max;

  static AABB AABBConstruct(const Math::Vector3& min,
                            const Math::Vector3& max) {
    Math::Vector3 center = 0.5f * (max + min);
    Math::Vector3 size = 2 * (max - center);
    return AABB(center, size);
  }

 public:
  AABB(const Math::Vector3& center, const Math::Vector3& size)
      : center{center}, size{size} {
    extents = 0.5 * size;
    min = center - extents;
    max = center + extents;
  }

  inline Math::Vector3 GetCenter() const { return center; }
  inline Math::Vector3 GetSize() const { return size; }
  inline Math::Vector3 GetExtents() const { return extents; }
  inline Math::Vector3 GetMin() const { return min; }
  inline Math::Vector3 GetMax() const { return max; }

  bool Contains(const Math::Vector3& point) const;
  bool Contains(const AABB& aabb) const;

  bool Intersect(const AABB& other) const;
  static bool Intersect(const AABB* a, const AABB* b);

  bool Raycast(const class Ray& ray, class RaycastHit* const hitInfo,
               float maxDistance = 0);

  void Expand(const float amount);

  void Encapsulate(const Math::Vector3& point);
  void Encapsulate(const AABB& other);
  static AABB Encapsulate(const AABB& a, const AABB& b);

  float SurfaceArea() const {
    return 2 * (size.x * size.y + size.y * size.z + size.x * size.z);
  }
};

} 