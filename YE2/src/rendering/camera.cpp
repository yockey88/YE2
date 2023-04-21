#include "rendering/camera.hpp"

namespace YE {
namespace rendering {

    Camera::Camera() {
        m_View_matrix = glm::mat4(1.f);
        m_Projection_matrix = glm::mat4(1.f);

        m_Position = glm::vec3{ 0.0f , 0.0f , 0.0f };
        m_Front = glm::vec3{ 0.0f , 0.0f , -1.0f };
        m_Up = glm::vec3{ 0.0f , 1.0f , 0.0f };
        m_Right = glm::vec3{ 1.0f , 0.0f , 0.0f };
        m_World_up = glm::vec3{ 0.0f , 1.0f , 0.0f };
    }
    
    void Camera::Recalculate() {
        m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front.y = sin(glm::radians(m_Pitch));
        m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(m_Front);

        m_Right = glm::normalize(glm::cross(m_Front , m_World_up));
        m_Up = glm::normalize(glm::cross(m_Right , m_Front));

        CalculateProjectionMatrix();
        CalculateViewMatrix();
    }

    void Camera::KeyboardCallback(SDL_Event* e) {
        switch (e->type) {
            case SDL_KEYDOWN:
                switch (e->key.keysym.sym) {
                    case SDLK_w: m_Position += m_Front * m_Speed; break;
                    case SDLK_s: m_Position -= m_Front * m_Speed; break;
                    case SDLK_a: m_Position -= m_Right * m_Speed; break;
                    case SDLK_d: m_Position += m_Right * m_Speed; break;
                    case SDLK_LSHIFT: m_Position += glm::vec3(0.f , 1.f , 0.f) * m_Speed; break;
                    case SDLK_LCTRL:  m_Position -= glm::vec3(0.f , 1.f , 0.f) * m_Speed; break;
                    default: break;
                }
            break;
        }
        CalculateProjectionMatrix();
        CalculateViewMatrix();
    }
    
    void Camera::MouseCallback(SDL_Event* e){
        m_Mouse_last_x = m_Mouse_x;
        m_Mouse_last_y = m_Mouse_y;

        int x, y;
        SDL_GetGlobalMouseState(&x, &y);
        m_Mouse_x = (float)x;
        m_Mouse_y = (float)y;

        int relx , rely;
        SDL_GetRelativeMouseState(&relx , &rely);
        m_Mouse_x_offset = m_Mouse_x - m_Mouse_last_x;
        m_Mouse_y_offset = m_Mouse_last_y - m_Mouse_y;

        switch (e->type) {
            case SDL_MOUSEMOTION:
                m_Yaw += relx * m_Sensitivity;
                m_Pitch += -1 * rely * m_Sensitivity;
                if (m_Constrain_pitch) {
                    if (m_Pitch > 89.0f) m_Pitch = 89.0f;
                    if (m_Pitch < -89.0f) m_Pitch = -89.0f;
                }
                m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
                m_Front.y = sin(glm::radians(m_Pitch));
                m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
                m_Front = glm::normalize(m_Front);
                m_Right = glm::normalize(glm::cross(m_Front , m_World_up));
                m_Up = glm::normalize(glm::cross(m_Right , m_Front));
            break;
        }
        CalculateProjectionMatrix();
        CalculateViewMatrix();
    }

}
}