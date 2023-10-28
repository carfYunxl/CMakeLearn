#include "Shape.h"
#include "glad/glad.h"
#include "VertextBuffer.h"
// #include "Texture.h"
#include "IndexBuffer.h"

namespace GL
{
    Triangle::Triangle(const char* imagepath)
    {
        m_vertexArray.Bind();
        m_vertexBuffer = std::make_unique<VertexBuffer>(m_Vertices.data(), m_Vertices.size()*sizeof(float)); 
        m_vertexBuffer->Bind();

        m_indexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size() * sizeof(unsigned));
        m_indexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // m_Texture = std::make_unique<Texture>(imagepath);
        // m_Texture->Bind();

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

    Rectangle::Rectangle(const char* imagepath)
    {
        m_vertexArray.Bind();
        m_vertexBuffer = std::make_unique<VertexBuffer>(m_Vertices.data(), m_Vertices.size() * sizeof(float)); 
        m_vertexBuffer->Bind();

        m_indexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size() * sizeof(unsigned int));
        m_indexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // m_Texture = std::make_unique<Texture>(imagepath);
        // m_Texture->Bind();

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