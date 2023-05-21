#pragma once
#include <unordered_set>
#include "Collisions/Collider.h"
#include "Util.h"

namespace Engine::CollisionUtil {
using CollisionPair = std::pair<Collider*, Collider*>;
using ColliderPairSet =
    std::unordered_set<CollisionPair, Util::UnorderedPairHash,
                       Util::UnorderedPairHash>;
}  // namespace Engine::CollisionUtil
