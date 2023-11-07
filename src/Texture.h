#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <vector>
#include "glad/glad.h"

namespace GL
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void Bind(uint32_t slot) const ;
        void UnBind(uint32_t slot) const { glBindTexture(GL_TEXTURE_2D + slot, 0); }

        unsigned int const GetTexture(uint32_t index) const {return m_Textures[index];}

        void LoadTexture(const char* filepath);

        void BindAll() const;
        void UnBindAll() const;

    private:
        std::vector<unsigned int> m_Textures;   //最多32
        unsigned int m_InternalFormat;
        unsigned int m_DataFormat;
        int m_Width;
        int m_Height;
    };
}


#endif //TEXTURE_H_