#include <gtest/gtest.h>

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

#include <glm/glm.hpp>

TEST(Engine , Initialization) {

    SUCCEED();

}

int main(int argc, char* argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}