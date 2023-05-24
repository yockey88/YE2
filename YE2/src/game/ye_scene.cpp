#include "game/ye_scene.hpp"
#include "game/ye_entity.hpp"
#include "game/entity_components.hpp"

#include "log.hpp"

namespace YE {
namespace game {

    Entity Scene::CreateEntity(uint32_t id , const std::string& name) {

        Entity ent(registry.create());
        ent.SetContext(this);

        auto& id_comp = ent.AddComponent<EntID>(id , name); // Add ID component to every entity upon creation

        return ent;

    }

    void Scene::DestroyEntity(Entity& ent) {

        if (registry.valid(ent.Handle())) {

            registry.destroy(ent.Handle());

        } else {

            YE_ERROR("Attempted to destroy invalid entity");

        }

    }

}
}