#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

namespace GL
{
    class IndexBuffer
    {
    public:
        IndexBuffer(unsigned int* buffer, unsigned int size);
        ~IndexBuffer();

        void Bind();
        void UnBind(); 
    private:
        unsigned int    m_IBO{0};
        unsigned int*          m_Buffer{nullptr};
        unsigned int    m_Size{0};
    };
}
#endif //INDEX_BUFFER_H