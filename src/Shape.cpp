#include "Shape.h"
#include "glad/glad.h"
#include "VertextBuffer.h"
#include "IndexBuffer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glfw3.h"

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
    }

    Cube::Cube(Shader& shader)
        : m_Shader(shader)
    {
        m_vertexArray.Bind();
        m_vertexBuffer = std::make_unique<VertexBuffer>(m_Vertices.data(), m_Vertices.size() * sizeof(float)); 
        m_vertexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        m_vertexArray.UnBind();
    }

    Cube::~Cube()
    {
        m_vertexArray.UnBind();
    }

    void Cube::Draw(const Camera& camera, const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale, uint32_t& draw_mode)
    {
        m_Shader.SetMat4(
            "u_Model", 
                glm::rotate(
                    glm::mat4(1.0f) 
                    , glm::radians(rotation.x)
                    , {1,0,0}
                    ) *
                glm::rotate(
                    glm::mat4(1.0f) 
                    , glm::radians(rotation.y)
                    , {0,1,0}
                ) *
                glm::rotate(
                    glm::mat4(1.0f) 
                    , glm::radians(rotation.z)
                    , {0,0,1}
                ) *
                glm::translate(
                    glm::mat4(1.0)
                    , {pos.x,pos.y,pos.z}
                    )*
                glm::scale(
                    glm::mat4(1.0f)
                    , scale
                ) 
                );
        // view matrix
        m_Shader.SetMat4("u_View", camera.GetView());
        m_Shader.SetMat4("u_Projection", camera.GetProjection());

        m_vertexArray.Bind();
        glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}