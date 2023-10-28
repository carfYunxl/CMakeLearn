#include "Shape.h"
#include "glad/glad.h"
#include "VertextBuffer.h"
// #include "Texture.h"
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

    Cube::Cube(Shader& shader, const char* imagepath)
        : m_Shader(shader)
    {
        m_vertexArray.Bind();
        m_vertexBuffer = std::make_unique<VertexBuffer>(m_Vertices.data(), m_Vertices.size() * sizeof(float)); 
        m_vertexBuffer->Bind();

        // m_indexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size() * sizeof(unsigned int));
        // m_indexBuffer->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // m_Texture = std::make_unique<Texture>(imagepath);
        // m_Texture->Bind();

        m_vertexArray.UnBind();
    }

    Cube::~Cube()
    {
        m_vertexArray.UnBind();
    }

    void Cube::Draw(const glm::vec3& pos, float rotation, float scale)
    {
        m_Shader.Set4f("u_Color", {1.0f, 0.5f, 0.2f, 1.0f });
        m_Shader.SetMat4(
            "u_Model", 
                glm::rotate(
                    glm::mat4(1.0f) 
                    , glm::radians(rotation)
                    , {0,1,0}
                    ) *
                glm::scale(
                    glm::mat4(1.0f)
                    , {scale,scale,scale}
                    ) * 
                glm::translate(
                    glm::mat4(1.0)
                    , {pos.x,pos.y,pos.z}
                    )
                );
        // view matrix
        float CamX = sin(glfwGetTime()) * 3.0f;
        float CamZ = cos(glfwGetTime()) * 3.0f;
        auto view = glm::lookAt(glm::vec3(CamX, 0.0f, CamZ), glm::vec3(0.0f,0.0f,0.0f), {0.0f,1.0f,0.0f});
        m_Shader.SetMat4("u_View", view);
        m_Shader.SetMat4("u_Projection", glm::perspective(glm::radians(45.0f), 1.778f, 0.1f, 100.0f));

        m_vertexArray.Bind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}