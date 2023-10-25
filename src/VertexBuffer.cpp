#include "glad/glad.h"
#include "VertextBuffer.h"
#include "Gl_Data.h"

namespace GL
{
    VertexBuffer::VertexBuffer()
    {
        Init();
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &VBO);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Data2D::g_vertices), Data2D::g_vertices, GL_STATIC_DRAW);
    }

    void VertexBuffer::UnBind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void VertexBuffer::Init()
    {
        glGenBuffers(1, &VBO);
    }
}