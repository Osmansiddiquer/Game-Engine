#pragma once
#include "Collisions/Collider.h"

namespace Engine {
DEFINE_COMPONENT(SphereCollider, Collider, false)
private:
#if _EDITOR
void Update() override;
#endif

protected:
ColliderType GetType() const final { return ColliderType::SPHERE; }

public:
/**
 * @brief radius of sphere before scale
 *
 */
float radius;

/**
 * @brief Construct a new Sphere Collider object
 *
 * @param radius multiplied by trasform scale
 */
explicit SphereCollider(const float radius = 0.5)
    : Collider{}, radius{radius} {}
/**
 * @brief Construct a new Sphere Collider object
 *
 * @param center offset from transform position
 * @param radius scaled by max transform scale not in direction
 */
explicit SphereCollider(const Math::Vector3& center, const float radius = 0.5)
    : Collider{center}, radius{radius} {}
/**
 * @brief Construct a new Sphere Collider object
 *
 * @param trigger whether collidable or trigger
 * @param center offset from transform position
 * @param radius scaled by max transform scale not in direction
 */
SphereCollider(bool trigger, const Math::Vector3& center, float radius = 0.5)
    : Collider{trigger, center}, radius{radius} {}

/**
 * @brief Cast ray at SphereCollider to determine RaycastHit.
 *
 * @param ray which is being cast
 * @param hitInfo information associated with a hit of box and ray
 * @param maxDistance that the ray will check against
 * @return true ray intersected collider
 */
bool Raycast(const Ray& ray, RaycastHit* const hitInfo,
             float maxDistance = 0) final;

float GetWorldRadius() const {
  return radius * transform->GetWorldScale().Max();
}

AABB GetFatAABB() final;
AABB GetAABB() final;

bool Intersection(Collider* const other) final;
DEFINE_COMPONENT_END(SphereCollider, Collider)
}  // namespace Engine
