#include "pch.h"
#include "Camera.h"

namespace GL{
    Camera::Camera(float Aspectio)
        : m_Aspectio(Aspectio), m_cPos{120.0f, 50.0f, 120.0f}, m_Yaw{-135.0f}, m_Pitch{-45.0f}, m_Zoom{45.0f}
    {
        Update();
    }
    Camera::~Camera()
    {

    }

    void Camera::Update()
    {
        // calculate camera front
        glm::vec3 cmFront{
            cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
            sin(glm::radians(m_Pitch)),
            sin(glm::radians(m_Yaw) * cos(glm::radians(m_Pitch)))
            };

        m_cFront = glm::normalize(cmFront);
        m_cRight = glm::normalize(glm::cross(m_cFront,g_Up));
        m_cUp = glm::normalize(glm::cross(m_cRight,m_cFront));

        m_View = glm::lookAt( m_cPos, m_cPos + m_cFront ,m_cUp );

        m_Projection = glm::perspective(m_Zoom, m_Aspectio, 0.1f, 1000.0f);
    }
}