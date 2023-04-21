#ifndef YE2_HPP
#define YE2_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "reactphysics3d/reactphysics3d.h"

#include "parsers/config_parser.hpp"

#include "rendering/SDL2.hpp"
#include "rendering/vertex.hpp"
#include "rendering/shader.hpp"
#include "rendering/texture.hpp"
#include "rendering/camera.hpp"
#include "rendering/frame_buffer.hpp"


// End of Testing Data

// std::unique_ptr<Cube> cube2 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube3 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube4 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube5 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube6 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube7 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube8 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube9 = std::make_unique<Cube>();
// std::unique_ptr<Cube> cube10 = std::make_unique<Cube>();

// std::unique_ptr<Cube> cubes[] = { std::move(cube)  , std::move(cube2) , std::move(cube3) , std::move(cube4) , std::move(cube5) ,
//                  std::move(cube6) , std::move(cube7) , std::move(cube8) , std::move(cube9) , std::move(cube10) };

// glm::vec3 cub_pos[] = {
//     glm::vec3(0.0f , 0.0f , 0.0f) ,
//     glm::vec3(2.0f , 5.0f , -15.0f) ,
//     glm::vec3(-1.5f , -2.2f , -2.5f) ,
//     glm::vec3(-3.8f , -2.0f , -12.3f) ,
//     glm::vec3(2.4f , -0.4f , -3.5f) ,
//     glm::vec3(-1.7f , 3.0f , -7.5f) ,
//     glm::vec3(1.3f , -2.0f , -2.5f) ,
//     glm::vec3(1.5f , 2.0f , -2.5f) ,
//     glm::vec3(1.5f , 0.2f , -1.5f) ,
//     glm::vec3(-1.3f , 1.0f , -1.5f)
// };

// float yaw = -90.0f;
// float pitch = 0.0f;
// // float roll = 0.0f;
// float fov = 45.0f;

// float last_x = 400.0f;
// float last_y = 300.0f;


#endif // YE2_HPP