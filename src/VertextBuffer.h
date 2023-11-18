#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

namespace GL
{
    class VertexBuffer
    {
    public:
        VertexBuffer(unsigned int size);
        ~VertexBuffer();

        void Bind();
        void UnBind();

    private:
        unsigned int    m_VBO;
        unsigned int    m_Size{0};
    };
}
#endif //VERTEX_BUFFER_H