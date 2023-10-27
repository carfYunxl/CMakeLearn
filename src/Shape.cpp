#include "Shape.h"
#include "glad/glad.h"
#include "VertextBuffer.h"
#include "IndexBuffer.h"

namespace GL
{
    Triangle::Triangle()
    {
        m_vertexArray.Bind();
        m_vertexBuffer = new VertexBuffer(m_Vertices.data(), m_Vertices.size()*sizeof(float)); 
        m_vertexBuffer->Bind();

        m_indexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size() * sizeof(unsigned));
        m_indexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        m_vertexArray.UnBind();
    }

    Triangle::~Triangle()
    {
        m_vertexArray.UnBind();
    }

    void Triangle::Draw()
    {
        m_vertexArray.Bind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,0);
        m_vertexArray.UnBind();
    }

    Rectangle::Rectangle()
    {
        m_vertexArray.Bind();
        m_vertexBuffer = new VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(float)); 
        m_vertexBuffer->Bind();

        m_indexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size() * sizeof(unsigned int));
        m_indexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        m_vertexArray.UnBind();
    }

    Rectangle::~Rectangle()
    {
        m_vertexArray.UnBind();
    }

    void Rectangle::Draw()
    {
        m_vertexArray.Bind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
        //m_vertexArray.UnBind();
    }
}