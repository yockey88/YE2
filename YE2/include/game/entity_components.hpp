#ifndef YE_ENTITY_COMPONENTS_HPP
#define YE_ENTITY_COMPONENTS_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

#include "entt.hpp"

#include <string>

#include "game/native_scripted_entity.hpp"

namespace YE {
namespace game {

    struct EntID {

        uint32_t id;
        std::string name;

        EntID() : id(-1) , name("[< Test_Entity >]") {}
        EntID(uint32_t id) : id(id) , name("[< Test_Entity >]") {}
        EntID(const std::string& name) : id(-1) , name(name) {}
        EntID(uint32_t id , const std::string& name) : id(id) , name(name) {}

    };

    struct PositionComponent {

        glm::vec3 pos , size , rot;

        PositionComponent() : pos(glm::vec3(0.0f)) , size(glm::vec3(1.0f)) , rot(glm::vec3(0.0f)) {}
        PositionComponent(const glm::vec3& pos) : pos(pos) , size(glm::vec3(1.0f)) , rot(glm::vec3(0.0f)) {}
        PositionComponent(const glm::vec3& pos , const glm::vec3& size) : pos(pos) , size(size) , rot(glm::vec3(0.0f)) {}
        PositionComponent(const glm::vec3& pos , const glm::vec3& size , const glm::vec3& rot) : pos(pos) , size(size) , rot(rot) {}

        glm::mat4 GetModel() {

            glm::mat4 qrot = glm::toMat4(glm::quat(rot));
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, pos) * qrot * glm::scale(model, size);
            return model;
            
        }

    };

    struct NativeScript {

        NativeScriptedEntity* instance = nullptr;
        
        NativeScriptedEntity*(*BindNativeScript)() = nullptr;
        void(*DestroyNativeScript)(NativeScript*) = nullptr;

        bool bound = false;

        NativeScript() {}
        ~NativeScript() {}

        template<typename T>
        void Bind() {

            BindNativeScript = []() { return static_cast<NativeScriptedEntity*>(new T()); };
            instance = BindNativeScript();

            DestroyNativeScript = [](NativeScript* script) {
                
                if (script->instance != nullptr) {
                    
                    delete script->instance;
                    script->instance = nullptr;

                } else {

                    YE_ERROR("NativeScript::DestroyNativeScript() called on invalid scripting instance (nullptr)")

                }

            };

            bound = true;

        }

        void Unbind() {

            DestroyNativeScript(this);

            BindNativeScript = nullptr;
            DestroyNativeScript = nullptr;

            bound = false;

        }

    };

}
}

#endif