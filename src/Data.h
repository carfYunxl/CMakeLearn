#ifndef DATA_H_
#define DATA_H_

#include "glm/glm.hpp"
#include "TimeStep.h"

namespace GL
{
    struct Attribute
    {
        glm::vec3   m_Pos{0.0f, 0.0f, 0.0f};
        glm::vec3   m_Rotation{0.0f, 0.0f, 0.0f};
        glm::vec3   m_Scale{100.0f, 5.0f, 100.0f};
        glm::vec3   m_Color{1.0f, 0.5f, 0.31f};
        bool        m_LineMode{false};
    };
}



#endif //DATA_H_