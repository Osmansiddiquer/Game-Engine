/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <unordered_map>
#include <vector>
#include "Core/Config/CVar.h"
#include "Core/Core.h"

template <typename... T>
using Action = std::function<void(T...)>;

template <typename result, typename... T>
using Func = std::function<result(T...)>;

namespace Engine {
template <typename T>
class LevelRegistry {
 protected:
  static bool registered;
};

class ENGINE_API LevelManager {
 private:
  std::vector<std::string> levelNames;
  std::unordered_map<std::string, Func<class Level*>> levels;
  class Level* pendingLoadLevel{nullptr};

  void LoadLevel();
  void UnloadLevel();
  friend class EngineLoop;

 public:
  struct LevelConfig {
    CVarString startLevel{"start_level", "EmptyLevel"};
  };

  /// Access the current loaded level
  class Level* loadedLevel{nullptr};

  static LevelManager& Instance();

  /**
   * \brief Used internally
   */
  bool Register(const std::string_view, Func<class Level*>);
  /**
   * \brief Get names of all levels registered
   */
  std::vector<std::string> GetLevelNames() const;

  LevelManager() = default;
  ~LevelManager() = default;
  /**
   * \brief Load the level with the given level name
   */
  void LoadLevel(std::string_view levelName);
};

template <typename T>
bool LevelRegistry<T>::registered =
    LevelManager::Instance().Register(T::GetLevelName(), T::CreateMethod);
}  // namespace Isetta
