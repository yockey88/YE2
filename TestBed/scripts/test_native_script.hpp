#include "game/ye_entity.hpp"

class TestScript : public YE::game::NativeScriptedEntity {

    public:
        TestScript() {}
        ~TestScript() {}

        virtual void Create() override {

            YE_TRACE("TestScript created!");

        }
         
        virtual void Update() override {

            YE_TRACE("TestScript updated!");

        }

        virtual void Destroy() override {

            YE_TRACE("TestScript destroyed!");

        }

};