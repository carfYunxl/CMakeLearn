#include "pch.h"
#include "BatchRender_3D.hpp"
#include "GL_Utils.hpp"
#include <filesystem>

namespace GL
{
    BatchRender_3D::BatchRender_3D()
    {
        m_pVAO = std::make_unique<VertexArray>();
        m_pVBO = std::make_unique<VertexBuffer>(m_MaxVertices * 36 * 8 * sizeof(float));

        m_Shader = std::make_unique<Shader>();
        m_Texture = std::make_unique<Texture>();

        m_pVAO->Bind();
        m_pVBO->Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        m_pVAO->UnBind();

        m_Vertices.resize(m_MaxVertices * 36);
    }

    BatchRender_3D::~BatchRender_3D(){
    }

    void BatchRender_3D::LoadShader(const char* shader_src)
    {
        m_Shader->LoadShader(shader_src);
    }

    void BatchRender_3D::LoadTexture(const char* texture_src)
    {
        m_Texture->LoadTexture(texture_src);
    }

    void BatchRender_3D::OnAttach()
    {
        std::filesystem::path current_path = std::filesystem::current_path();
        std::filesystem::path Path = current_path / "texture" / "wall.jpg";
        m_Texture->LoadTexture(Path.string().c_str());

        std::filesystem::path bPath = current_path / "shaders" / "Basic.shader";
        std::filesystem::path sPath = current_path / "shaders" / "Obj.shader";
        std::filesystem::path lPath = current_path / "shaders" / "Light.shader";

        m_Shader->LoadShader(bPath.string().c_str());
    }

    void BatchRender_3D::OnDrawCube(const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale)
    {
        glm::mat4 transform = 
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
                    ) ;

        m_pVAO->Bind();
        

        for( int i = 0;i <  g_vecGet.size();++i)
        {
            glm::vec4 re = transform * glm::vec4{ g_vecGet[i].Pos.x, g_vecGet[i].Pos.y, g_vecGet[i].Pos.z, 1.0f };
            m_Vertices[m_UsedVertices].Pos = POS{re.x, re.y, re.z};

            re = transform * glm::vec4{ g_vecGet[i].Tex.x, g_vecGet[i].Tex.y, 1.0f, 1.0f };
            m_Vertices[m_UsedVertices].Tex = TEX{re.x, re.y};

            re = transform * glm::vec4{ g_vecGet[i].Norm.x, g_vecGet[i].Norm.y, g_vecGet[i].Norm.z, 1.0f };
            m_Vertices[m_UsedVertices].Norm = NORM{re.x, re.y, re.z};

            m_UsedVertices++;

        }

        m_CubeCnt++;

        if( m_UsedVertices >= m_MaxVertices * 36 )
        {
            EndScene();
        }
    }

    void BatchRender_3D::OnDetach()
    {

    }

    void BatchRender_3D::BeginScene(const Camera& camera)
    {
        m_Camera = camera;

        m_pVAO->Bind();
        // shader attribute
        m_Shader->Bind();
        m_Shader->SetInt("u_Texture", 0);
        m_Shader->SetFloat("u_Repeat", m_Repeat );
        // texture attribute
        m_Shader->SetMat4( "u_Model", glm::mat4(1.0f) );
        // view matrix
        m_Shader->SetMat4("u_View", camera.GetView());
        m_Shader->SetMat4("u_Projection", camera.GetProjection());
        m_Texture->Bind(0);
    }

    void BatchRender_3D::EndScene()
    {
        m_pVBO->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_UsedVertices * 8 *sizeof(float), (float*)m_Vertices.data());
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<uint32_t>(m_PolygonMode));
        glDrawArrays(GL_TRIANGLES, 0, 36 * m_CubeCnt);

        m_Vertices.clear();
        m_Vertices.resize(m_MaxVertices * 36);
        m_UsedVertices = 0;
        m_CubeCnt = 0;

        m_DrawCalls++;
    }

    void BatchRender_3D::SetDrawMode(PolygonMode mode)
    {
        m_PolygonMode = mode;
    }
}