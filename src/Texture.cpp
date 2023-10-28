#include "pch.h"
#include "Texture.h"
#include "stb_image.h"

namespace GL
{
    Texture::Texture(const char* filepath)
        : m_filepath(std::move(filepath))
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width = 0,height = 0, channels = 0;
        unsigned char* data = stbi_load(m_filepath, &width, &height, &channels, 0);
        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{
            std::cout << "failed to load image !" << std::endl;
        }

        stbi_image_free(data);
    }
    Texture::~Texture()
    {
        glDeleteTextures(1, &texture);
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}