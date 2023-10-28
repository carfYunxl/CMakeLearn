#ifndef SHAPE_H_
#define SHAPE_H_

#include "VertexArray.h"
#include <vector>
#include <memory>

namespace GL
{
    struct VertexBuffer;
    struct IndexBuffer;
    // struct Texture;

    class Triangle
    {
    public:
        explicit Triangle(const char* imagepath);
        ~Triangle();

        void Draw();
    private:
        VertexArray                     m_vertexArray;
        std::unique_ptr<VertexBuffer>   m_vertexBuffer;
        std::unique_ptr<IndexBuffer>    m_indexBuffer;
        // std::unique_ptr<Texture>        m_Texture;

        std::vector<float>          m_Vertices{
                0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
                0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
                0.25f, 0.5f, 0.0f, 0.5f, 1.0f
                };
        std::vector<unsigned int>   m_Indices{
              0,1,2
        };
    };

    class Rectangle
    {
    public:
        explicit Rectangle(const char* imagepath);
        ~Rectangle();

        void Draw();
    private:
        VertexArray                     m_vertexArray;
        std::unique_ptr<VertexBuffer>   m_vertexBuffer;
        std::unique_ptr<IndexBuffer>    m_indexBuffer;
        // std::unique_ptr<Texture>        m_Texture;

        std::vector<float>              m_Vertices{
        // positions        // texture coords
         0.0f,  0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.0f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        std::vector<unsigned int>   m_Indices{
              0,1,3,
              1,2,3
        };
    };
}

#endif //SHAPE_H_