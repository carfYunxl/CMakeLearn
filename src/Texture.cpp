#include "pch.h"
#include "Texture.h"
#include "stb_image.h"

namespace GL
{
    Texture::Texture(const char* filepath)
        : m_filepath(std::move(filepath))
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filepath, &width, &height, &channels, 0);

        m_Width = width;
        m_Height = height;

        if( !data )
            std::cout << "Fail to load image!" << std::endl;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        glCreateTextures(GL_TEXTURE_2D, 1, &texture);
        glTextureStorage2D(texture, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(texture, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
    
        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &texture);
    }

    void Texture::Bind() const 
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}