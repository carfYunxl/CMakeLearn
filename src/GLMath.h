#ifndef GL_MATH_H_
#define GL_MATH_H_

#include "glm.hpp"

namespace GL
{
    bool ExtractTRS(const glm::mat4& transform, glm::vec3& translate, glm::vec3& rotate, glm::vec3& scale);
}

#endif //GL_MATH_H_