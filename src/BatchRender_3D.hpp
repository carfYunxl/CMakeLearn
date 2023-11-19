#ifndef BATCH_RENDER_HPP_
#define BATCH_RENDER_HPP_

#include <memory>
#include <cstdint>
#include <vector>
#include "GL_Utils.hpp"
#include "VertexArray.h"
#include "VertextBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Scene/Components.h"

namespace GL
{
    enum class PolygonMode
    {
        LINE = 0x1B01,
        FILL = 0x1B02
    };

    class BatchRender_3D
    {
    public:

        BatchRender_3D(ColorComponent& color);
        ~BatchRender_3D();

        void LoadShader(const char* shader_src);
        void LoadTexture(const char* texture_src);

        void OnAttach();
        void OnDrawCube(const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale);
        void OnDetach();

        void BeginScene(const Camera& camera);
        void EndScene();

        void SetDrawMode(PolygonMode mode);
        uint32_t GetDrawMode(){return static_cast<uint32_t>(m_PolygonMode);}

        void ResetDrawCall(){m_DrawCalls = 0;}
        float GetDrawCall(){return m_DrawCalls;}

        float* GetMaxVertices(){return &m_MaxVertices;}
        float* GetRepeat(){return &m_Repeat; }

        void DrawCube(const glm::mat4& transform, const glm::vec4& color);

         ColorComponent& GetColorCom() const {return m_ColorCom;}
         void SetColorCom(ColorComponent& color) {m_ColorCom = color;}

    private:

        std::unique_ptr<VertexArray>    m_pVAO;
        std::unique_ptr<VertexBuffer>   m_pVBO;

        std::unique_ptr<Shader>         m_Shader;
        std::unique_ptr<Texture>        m_Texture;

        Camera                          m_Camera{1.778f};
        PolygonMode                     m_PolygonMode;
    private:

        // other private variable to notify the VBO states
        uint32_t m_UsedVertices{0};
        uint32_t m_CubeCnt{0};

        // vertices 
        // TODO
        // std::vector<float>              m_Vertices;

        std::vector<BufferLayout> m_Vertices;

        float m_Repeat{5.0f};

        float m_DrawCalls{0.0f};

        float m_MaxVertices{1000.0f};
        
        ColorComponent& m_ColorCom;
    };
}

#endif