#ifndef DATA_H_
#define DATA_H_

#include "glm/glm.hpp"
#include "TimeStep.h"

namespace GL
{
    struct SceneData
    {
        glm::vec3   m_ObjPos{0.0f, 0.0f, 0.0f};
        glm::vec3   m_ObjRotation{0.0f, 0.0f, 0.0f};
        glm::vec3   m_ObjColor{1.0f, 0.5f, 0.31f};
        glm::vec3   m_ObjScale{100.0f, 5.0f, 100.0f};

        glm::vec3   m_LightPos{0.0f, 20.0f, 0.0f};
        glm::vec3   m_LightRotation{0.0f, 0.0f, 0.0f};
        glm::vec3   m_LightColor{1.0f, 1.0f, 1.0f};
        glm::vec3   m_LightScale{5.0f, 5.0f, 5.0f};

        float       m_lastFrameTime{0.0f};
        Timestep    m_TS = 0.0f;
        int         m_WIDTH = 1920;
        int         m_HEIGHT = 1080;
        float       m_LastX{ (float)m_WIDTH/2 };
        float       m_LastY{ (float)m_HEIGHT/2 };
    };
}



#endif //DATA_H_