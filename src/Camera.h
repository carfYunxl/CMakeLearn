#ifndef CAMERA_H_
#define CAMERA_H_
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GL{

    constexpr glm::vec3 g_Up{0.0f, 1.0f, 0.0f}; //全局坐标系上向量

    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;

    class Camera
    {
    public:
        explicit Camera(float Aspectio);
        ~Camera();

        const glm::mat4& GetView() const {return m_View;}

        const float GetYaw() const { return m_Yaw; }
        void SetYaw(float yaw) { m_Yaw = yaw; Update(); }
        void AddYaw(float add) { m_Yaw += add; Update(); }

        const float GetPitch() const { return m_Pitch; }
        void SetPitch(float pitch) { m_Pitch = pitch; Update(); }
        void AddPitch(float add) { m_Pitch += add; Update(); }

        const glm::vec3& GetCameraPos() const { return m_cPos; }
        void SetCameraPos(const glm::vec3& pos) { m_cPos = pos; Update(); }
        void AddCameraPos(const glm::vec3& add) { m_cPos += add; Update(); }
        void SubCameraPos(const glm::vec3& add) { m_cPos -= add; Update(); }

        const glm::mat4 GetProjection() const {return m_Projection;}

        void AddZoom(float zoom) { m_Zoom += zoom; Update(); }
        const float GetZoom() const { return m_Zoom; }
        void SetZoom(float zoom) { m_Zoom = zoom; Update(); }

        void SetAspectio(float asp) { m_Aspectio = asp; Update(); }


        const glm::vec3& GetFront() {return m_cFront;}
        const glm::vec3& GetRight() {return m_cRight;}

        const glm::vec3& GetUp() {return m_cUp;}
        void AddUp(const glm::vec3& add) {
            m_cUp += add;
            Update();
            }


        void Update();
    private:
        glm::vec3   m_cPos;     //camera pos
        glm::vec3   m_cFront;   //camera front
        glm::vec3   m_cRight;   //camera right
        glm::vec3   m_cUp;      //camera up

        glm::mat4   m_View;
        glm::mat4   m_Projection;

        float       m_Yaw{-90.0f};
        float       m_Pitch{0.0f};

        float       m_Zoom{45.0f};
        float       m_Aspectio{1.778f};
    public:
        bool g_isFirstMouse {true};
        float g_LastX{WIDTH/2};
        float g_LastY{HEIGHT/2};
        float g_MoveSpeed{190.0f};
        float g_Sensitivity{0.1f};
    };

}


#endif //CAMERA_H_