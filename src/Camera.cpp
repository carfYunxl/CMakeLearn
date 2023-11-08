#include "pch.h"
#include "Camera.h"
#include "WindowsInput.h"
#include "KeyCodes.h"

namespace GL
{
    Camera::Camera(float Aspectio)
        : m_Aspectio(Aspectio), m_cPos{150.0f, 0.0f, 0.0f}, m_Yaw{-180.0f}, m_Pitch{0.0f}, m_Zoom{45.0f}
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
        m_cRight = glm::normalize(glm::cross(m_cFront,m_GlobalUp));
        m_cUp = glm::normalize(glm::cross(m_cRight,m_cFront));

        m_View = glm::lookAt( m_cPos, m_cPos + m_cFront ,m_cUp );

        m_Projection = glm::perspective(m_Zoom, m_Aspectio, 0.1f, m_ViewDistance);
    }

    void Camera::OnUpdate(Timestep ts)
    {
        m_ts = ts;
        float move_velocity = m_MoveSpeed * ts;
        float rotate_velocity = m_MoveSpeed * ts;

        if( WindowsInput::IsKeyPressed(Key::W) )
        {
            m_cPos += move_velocity * m_cFront;
            Update();
        }

        if(WindowsInput::IsKeyPressed(Key::S))
        {
            m_cPos -= move_velocity * m_cFront;
            Update();
        }

        if(WindowsInput::IsKeyPressed(Key::A))
        {
            m_cPos -= move_velocity * glm::normalize(glm::cross(m_cFront,m_cUp));
            Update();
        }

        if(WindowsInput::IsKeyPressed(Key::D))
        {
            m_cPos += move_velocity * glm::normalize(glm::cross(m_cFront,m_cUp));
            Update();
        }

        if(WindowsInput::IsKeyPressed(Key::Q))
        {
            m_cPos += move_velocity * m_cUp;
            Update();
        }

        if(WindowsInput::IsKeyPressed(Key::E))
        {
            m_cPos -= move_velocity * m_cUp;
            Update();
        }
    }

    void Camera::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Camera::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Camera::OnWindowResized));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Camera::OnMouseMoved));
    }

    void Camera::OnResize(float width, float height)
    {
        m_Aspectio = width / height;
        Update();
    }

    bool Camera::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_Zoom -= e.GetYOffset() * m_ts;

        if (m_Zoom < 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom > 90.0f)
            m_Zoom = 90.0f;

        Update();

        return false;
    }

    bool Camera::OnMouseMoved(MouseMovedEvent& e)
    {
        return true;
        float xpos = static_cast<float>(e.GetX());
        float ypos = static_cast<float>(e.GetY());
        
        if (m_isFirstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_isFirstMouse = false;
        }

        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos;

        m_LastX = xpos;
        m_LastY = ypos;

        m_Yaw += xoffset * m_Sensitivity;
        m_Pitch += yoffset * m_Sensitivity;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;

        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        Update();

        return false;
    }

    bool Camera::OnWindowResized(WindowResizeEvent& e)
    {
        OnResize((float)e.GetWidth(), (float)e.GetHeight());

        m_Projection = glm::perspective(glm::radians(m_Zoom), m_Aspectio, 0.1f, m_ViewDistance);

        return false;
    }
}