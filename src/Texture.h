#ifndef TEXTURE_H_
#define TEXTURE_H_

namespace GL
{
    class Texture
    {
    public:
        Texture(const char* filepath);
        ~Texture();

        void Bind() const ;
        void UnBind() const { glBindTexture(GL_TEXTURE_2D, 0); }

        unsigned int const GetTexture() const {return texture;}

    private:
        unsigned int texture;
        const char* m_filepath;

        unsigned int m_InternalFormat, m_DataFormat;
        int m_Width, m_Height;
    };
}


#endif //TEXTURE_H_