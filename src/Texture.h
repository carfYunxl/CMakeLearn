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

    private:
        unsigned int texture;
        const char* m_filepath;
    };
}


#endif //TEXTURE_H_