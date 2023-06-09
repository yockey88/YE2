#ifndef YE_CAMERA_HPP
#define YE_CAMERA_HPP

#include "SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace YE {
namespace rendering {

    /** Camera Class
     *   -> handles all camera information
     *   -> temporary implementation, will be replaced with a more robust system in the future that will allow 
     *          have different view and projection matrices for different cameras as well as allow for users to override camera behavior
     *          and create their own camera classes
    */
    class Camera {
        glm::mat4 m_View_matrix;
        glm::mat4 m_Projection_matrix;

        Camera(const Camera&) = delete;
        Camera(Camera&&) = delete;
        Camera& operator=(const Camera&) = delete;
        
        inline void CalculateViewMatrix() { m_View_matrix = glm::lookAt(m_Position , m_Position + m_Front , m_Up); }
        inline void CalculateProjectionMatrix() { m_Projection_matrix = glm::perspective(glm::radians(m_FOV) , m_View_width / m_View_height , m_Clipping_near , m_Clipping_far); }
        public:
            glm::vec3 m_Position;
            glm::vec3 m_Front;
            glm::vec3 m_Up;
            glm::vec3 m_Right;
            glm::vec3 m_World_up;

            float m_Yaw{ -90.0f };
            float m_Pitch{ 0.0f };
            float m_Roll{ 0.0f };
            float m_Speed{ 0.1f };
            float m_Sensitivity{ 0.2f };
            float m_FOV{ 45.0f };
            float m_Zoom{ 45.0f };
            float m_Clipping_near{ 0.1f };
            float m_Clipping_far{ 100.0f };
            float m_View_width{ 800.0f };
            float m_View_height{ 600.0f };

            float m_Mouse_last_x{ 400.0f };
            float m_Mouse_last_y{ 300.0f };
            float m_Mouse_x{ 0.0f };
            float m_Mouse_y{ 0.0f };
            float m_Mouse_x_offset{ 0.0f };
            float m_Mouse_y_offset{ 0.0f };
            bool m_Constrain_pitch{ true };

            Camera();
            ~Camera() {}

            void Recalculate();
            inline glm::mat4& GetViewMatrix() { return m_View_matrix; }
            inline glm::mat4& GetProjectionMatrix() { return m_Projection_matrix; }
            inline void GetViewMatrix(glm::mat4& viewMatrix) { viewMatrix = glm::lookAt(m_Position , m_Position + m_Front , m_Up); }
            inline void GetProjectionMatrix(glm::mat4& projectionMatrix) { projectionMatrix = glm::perspective(glm::radians(m_FOV) , m_View_width / m_View_height , m_Clipping_near , m_Clipping_far); }
            
            // Temporary camera movement functions
            void DefaultKeyboardCallback();
            void DefaultMouseCallback(SDL_Event* e);
    };

}
}

#endif