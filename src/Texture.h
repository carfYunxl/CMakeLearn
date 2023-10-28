#ifndef TEXTURE_H_
#define TEXTURE_H_

namespace GL
{
    class Texture
    {
    public:
        Texture(const char* filepath);
        ~Texture();

        void Bind();

        unsigned int const GetTexture() const {return texture;}

        void Reset(const char* filepath);

    private:
        unsigned int texture;
        const char* m_filepath;

        unsigned int m_InternalFormat, m_DataFormat;
        int m_Width, m_Height;
    };
}


#endif //TEXTURE_H_