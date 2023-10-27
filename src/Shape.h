#ifndef SHAPE_H_
#define SHAPE_H_

#include "VertexArray.h"
#include <vector>

namespace GL
{
    struct VertexBuffer;
    struct IndexBuffer;

    class Triangle
    {
    public:
        Triangle();
        ~Triangle();

        void Draw();
    private:
        VertexArray                 m_vertexArray;
        VertexBuffer*               m_vertexBuffer;
        IndexBuffer*                m_indexBuffer;
        std::vector<float>          m_Vertices{
                0.5f,  0.5f, 0.0f,
                0.0f,  0.5f, 0.0f,
                0.0f,  0.0f, 0.0f
                };
        std::vector<unsigned int>   m_Indices{
              0,1,2
        };
    };

    class Rectangle
    {
    public:
        Rectangle();
        ~Rectangle();

        void Draw();
    private:
        VertexArray                 m_vertexArray;
        VertexBuffer*               m_vertexBuffer;
        IndexBuffer*                m_indexBuffer;
        std::vector<float>          m_Vertices{
               -0.5f, -0.5f, 0.0f,
                0.0f, -0.5f, 0.0f,
                0.0f,  0.0f, 0.0f,
               -0.5f,  0.0f, 0.0f
                };
        std::vector<unsigned int>   m_Indices{
              0,1,3,
              1,2,3
        };
    };
}

#endif //SHAPE_H_