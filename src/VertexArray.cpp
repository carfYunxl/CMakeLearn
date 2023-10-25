#include "glad/glad.h"
#include "VertexArray.h"

namespace GL
{
    VertexArray::VertexArray()
    {
        Init();
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &VAO);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(VAO);
    }

    void VertexArray::UnBind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::Init()
    {
        glGenVertexArrays(1, &VAO);
    }
}