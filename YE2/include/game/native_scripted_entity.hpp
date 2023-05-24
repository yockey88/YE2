#ifndef YE_NATIVE_SCRIPTED_ENTITY_HPP
#define YE_NATIVE_SCRIPTED_ENTITY_HPP

#include "game/ye_entity.hpp"

namespace YE {
namespace game {

    class NativeScriptedEntity {

        friend class Scene;

        public:
        
            Entity entity;

            NativeScriptedEntity() {}
            ~NativeScriptedEntity() {}

            template<typename T>
            T& GetComponent() { return Entity().GetComponent<T>(); }

            template<typename T , typename... Args>
            T& AddComponent(Args&&... args) { return Entity().AddComponent<T>(std::forward<Args>(args)...); }

            template<typename T>
            bool HasComponent() { return Entity().HasComponent<T>(); }

            virtual void Create() {}
            virtual void Update() {}
            virtual void Destroy() {}

    };

}
}

#endif