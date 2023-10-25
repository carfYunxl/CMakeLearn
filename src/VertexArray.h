#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

namespace GL
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void UnBind();
    private:
        void Init();
    private:
        unsigned int VAO;
    };
}


#endif //VERTEX_ARRAY_H_