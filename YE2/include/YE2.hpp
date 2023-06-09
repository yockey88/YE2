#ifndef YE2_HPP
#define YE2_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "reactphysics3d/reactphysics3d.h"

#include "log.hpp"

#include "core/engine.hpp"
#include "core/engine_config.hpp"
#include "core/logger.hpp"

#include "input/keyboard.hpp"
#include "input/mouse.hpp"

#include "parsers/config_parser.hpp"

#include "rendering/window.hpp"
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

#define ENGINEY YE::Engine::Get()

#define YELOG YE::core::Logger::Get()
using LogType = YE::core::Logger::LogType;
using LogLevel = YE::core::Logger::LogLevel;

namespace YE {

     int Main(int argc , char* argv[]) {

        YE::YApp* app = YE::CreateApp();
        YE::Engine& engine = ENGINEY;

        if (!engine.Init(std::move(app))) {

            YE_FATAL("Engine Initialization Failed");
            delete app;
            app = nullptr;
            return 1;

        }

        engine.Run();
        engine.Shutdown();

        return 0;

    }

}

int main(int argc , char* argv[]) {

    return YE::Main(argc , argv);

}

#ifdef YE_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow) {

    return main(__argc , __argv);

}

#endif

#endif // YE2_HPP