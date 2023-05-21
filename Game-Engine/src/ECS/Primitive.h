/*
 * Copyright (c) 2018 Engine
 */
#pragma once
#include <string>
#include "Engine_API.h"

namespace Engine {
struct ENGINE_API Primitive {
  enum class Type {
    Capsule,
    Cube,
    Cylinder,
    Grid,
    Quad,
    Sphere,
  };
  /**
   * \brief Create a primitive with the given name, with the option to specific
   * if it has a collider attached
   */
  static class Entity* Create(Type type, const std::string_view name,
                              bool withCollider);
  /**
   * \brief Create a primitive, with the option to specific if it has a collider
   * attached
   */
  static class Entity* Create(Type type, bool withCollider = false);
};
}  // namespace Engine