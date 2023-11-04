#ifndef DATA_H_
#define DATA_H_

#include "glm/glm.hpp"
#include "TimeStep.h"

namespace GL
{
    struct GlobalData
    {
        float       m_lastFrameTime{0.0f};
        Timestep    m_TS = 0.0f;
        int         m_WIDTH = 1920;
        int         m_HEIGHT = 1080;
        float       m_LastX{ (float)m_WIDTH/2 };
        float       m_LastY{ (float)m_HEIGHT/2 };
    };

    struct Attribute
    {
        glm::vec3   m_Pos{0.0f, 0.0f, 0.0f};
        glm::vec3   m_Rotation{0.0f, 0.0f, 0.0f};
        glm::vec3   m_Scale{100.0f, 5.0f, 100.0f};
        glm::vec3   m_Color{1.0f, 0.5f, 0.31f};
    };
}



#endif //DATA_H_