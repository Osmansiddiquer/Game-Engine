#pragma once
#include <vector>
#include <memory>

class Component;

class Entity {
private:
    std::vector<std::shared_ptr<Component>> components;

public:
    void addComponent(std::shared_ptr<Component> component) {
        components.push_back(component);
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        for (const auto& component : components) {
            std::shared_ptr<T> target = std::dynamic_pointer_cast<T>(component);
            if (target) {
                return target;
            }
        }
        return nullptr;
    }

    template<typename T>
    bool hasComponent() const {
        return getComponent<T>() != nullptr;
    }
};

