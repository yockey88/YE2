#include "YE2.hpp"
#include "log.hpp"

#include "scripts/test_native_script.hpp"

#include <climits>
#include <chrono>
#include <stdio.h>

int main() {

    if (!ENGINEY.Init()) {

        std::cerr << "Failed to initialize EngineY" << std::endl;
        return 1;

    }

    { // Scene and Entity Testing
        
        // // require a scene to make an entity because an entity cannot exist without context for it to exist in
        // YE::game::Scene scene;
        // YE::game::Entity ent = scene.CreateEntity(1 , "TestEntity");

        // scene.registry.view<YE::game::EntID>().each([=](auto ent , auto& id) {

        //     YE_INFO("YE::game::Entity => <{}>::[{}]" , id.id , id.name);

        // });

        // auto& script = ent.AddComponent<YE::game::NativeScript>();

        // script.Bind<TestScript>();
        // script.instance->Create();

        // script.instance->Update();

        // script.instance->Destroy();
        // script.Unbind();

    }
    { // Scripting Engine Testing

        // Instantiate scripting engine 
        // YE::scripting::ScriptEngine script_engine;
        
        // // Initialize scripting engine
        // //      -> Creates root domain and app domain
        // //      -> Loads core engine dlls/scripts
        // if (!script_engine.Init()) {
            
        //     YE_ERROR("Failed to initialize ScriptEngine");
        //     return 1;

        // }

        // YE::scripting::ScriptEngineState* script_state = script_engine.GetState();
        // YE_ASSERT(script_state->script_engine_valid , "Script engine failed to initialize");

        // script_engine.PrintTypes();

        // // Get script assembly image
        // //     -> Used to get script class
        // //     -> Similar storage situation to assembly
        // MonoImage* image = mono_assembly_get_image(script_state->core_assembly);
        // YE_ASSERT(image != nullptr , "Failed to get script assembly image");

        // // Get class from assembly
        // //     -> Used to instantiate script object
        // //     -> Similar storage situation to assembly and image
        // // !!!=> I want to be able to grab YE_SCRIPT::<CLass_name> without explicitly stating
        // //          the namespace and name, then I can have more flexibility about allowing users to user their own 
        // //          namespaces and class names /!!! (Might not be possible, will have to rely on built in script classes getting extended)
        // MonoClass* klass = mono_class_from_name(image , "YE" , "ScriptTesting");
        // YE_ASSERT(klass != nullptr , "Failed to get script class");

        // MonoObject* object = script_engine.InstantiateObject(klass);
        // YE_ASSERT(object != nullptr , "Failed to instantiate script object");

        // MonoMethod* method = mono_class_get_method_from_name(klass , "MainTestFunc" , 0);
        // YE_ASSERT(method != nullptr , "Failed to get script method");

        // MonoObject* exception = nullptr;
        // mono_runtime_invoke(method , object , nullptr , &exception);
        // YE_ASSERT(exception == nullptr , "Failed to invoke script method");

    }

    YE::Engine::Get().Shutdown();
    
    return 0;

}