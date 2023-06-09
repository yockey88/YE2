#ifndef YE_SCENE_HPP
#define YE_SCENE_HPP

#include "entt.hpp"

#include <memory>
#include <map>

namespace YE {
namespace game {

    class Entity;

    class Scene {
        
        entt::registry registry;
        friend class Entity;

        public:

            Scene() {}
            ~Scene() {}

            inline entt::registry& GetEntities() { return registry; }

            Entity CreateEntity(uint32_t id = 0 , const std::string& name = "[< Blank_Entity >]");
            void DestroyEntity(Entity& ent);

            void Update();
            void Render();

    };

}
}

#endif