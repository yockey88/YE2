#ifndef YE_ENTITY_HPP
#define YE_ENTITY_HPP

#include "entt.hpp"
#include "entity/registry.hpp"

#include "log.hpp"

#include "game/ye_scene.hpp"

namespace YE {
namespace game {

    class Scene;

    class Entity {

        Scene* context;
        entt::entity handle;

        public:
            Entity() : handle(entt::null) {}
            Entity(entt::entity handle) : handle(handle) {}
            Entity(entt::entity handle , Scene* scene) : handle(handle) , context(scene) {}
            Entity(const Entity& other) : handle(other.handle) {}

            inline void SetContext(Scene* context) { this->context = context; }

            template<typename T , typename... Args>
            inline T& AddComponent(Args&&... args) { return context->registry.emplace<T>(handle, std::forward<Args>(args)...); }

            template<typename T , typename... Args>
            inline T& AddOrReplaceComponent(Args&&... args) { return context->registry.emplace_or_replace<T>(handle, std::forward<Args>(args)...); }

            template<typename T>
            inline T& GetComponent() {

                YE_ASSERT(HasComponent<T>(), "Entity does not have component!");
                return context->registry.get<T>(handle);

            }

            template<typename T>
            inline bool HasComponent() { return (context->registry.try_get<T>(handle) != nullptr); }

            template<typename T>
            inline void RemoveComponent() {

                YE_ASSERT(HasComponent<T>(), "Entity does not have component!");
                context->registry.remove<T>(handle);

            }

            inline entt::entity Handle() const { return handle; }
            inline bool Valid() const { return context->registry.valid(handle); }

    };

}
}

#endif