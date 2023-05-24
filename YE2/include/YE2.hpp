#ifndef YE2_HPP
#define YE2_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "reactphysics3d/reactphysics3d.h"

#include "core/engine_config.hpp"
#include "core/logger.hpp"

#include "parsers/config_parser.hpp"

#include "rendering/SDL2.hpp"
#include "rendering/vertex.hpp"
#include "rendering/shader.hpp"
#include "rendering/texture.hpp"
#include "rendering/camera.hpp"
#include "rendering/frame_buffer.hpp"

#include "game/ye_entity.hpp"
#include "game/ye_scene.hpp"
#include "game/entity_components.hpp"

#include "scripting/script_engine.hpp"

#include "temp_testing/TestMeshes.hpp"

#include <glm/glm.hpp>

#define ENGINEY YE::Engine::Get()

namespace YE {

    static std::unique_ptr<core::EngineConfiguration> engine_config = nullptr;

    /** EngineY Class
     *    -> Central engine class
    */
    class Engine {
        
        static Engine* engine_instance;

        core::Logger logger;

        std::unique_ptr<scripting::ScriptEngine> script_engine = nullptr;

        // private constructor to prevent instantiation
        //      Do nothing in constructor
        //      Simply hiding it from the public
        Engine() {}
        // Delete copy constructors and assign operators
        Engine(Engine&&) = delete;
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        // Internal initialization functions
        bool InitSystems();

        public:

            ~Engine();

            // Get the Engine instance
            static Engine& Get();

            // Public Initialization function
            bool Init();
            // Public Shutdown function
            void Shutdown();

    };

}


#endif // YE2_HPP