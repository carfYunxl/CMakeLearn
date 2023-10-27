#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

namespace GL
{
    class VertexBuffer
    {
    public:
        VertexBuffer(float* buffer, unsigned int size);
        ~VertexBuffer();

        void Bind();
        void UnBind();

        void Reset(float* buffer, unsigned int size);

    private:
        unsigned int    m_VBO;
        float*          m_Buffer{nullptr};
        unsigned int    m_Size{0};
    };
}
#endif //VERTEX_BUFFER_H