#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

namespace GL
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void UnBind();

        unsigned int GetVBO() const {return VBO;}

    private:
        void Init();

    private:
        unsigned int VBO;
    };
}
#endif //VERTEX_BUFFER_H