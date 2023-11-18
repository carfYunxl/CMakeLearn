#include "glad/glad.h"
#include "VertextBuffer.h"

namespace GL
{
    VertexBuffer::VertexBuffer(unsigned int size)
        : m_Size(size)
    {
        glGenBuffers(1, &m_VBO);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Size, nullptr, GL_STATIC_DRAW);
    }

    void VertexBuffer::UnBind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}