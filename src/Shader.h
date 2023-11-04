#ifndef SHADER_H_
#define SHADER_H_

#include "glm.hpp"
#include <memory>
#include <string>
#include "Data.h"

namespace GL
{
    // class Texture;

    class Shader
    {
        public:
            enum class ShaderType
            {
                NONE = 0,
                VERTEX,
                FRAGMENT
            };

            Shader(const char* shader_source);
            ~Shader();
            void Bind();
            void UnBind();

            unsigned int const GetProgram() const {return m_sProgram;}

            void Set4f(const char* name, const glm::vec4& color);
            void Set3f(const char* name, const glm::vec3& color);
            void SetInt(const char* name, unsigned int index);
            void SetFloat(const char* name, float val);
            void SetMat4(const char* name, const glm::mat4& trans);

            //void SetUniformAttr(const Attribute& data);

        private:
            unsigned int    Compile(const char* shader, unsigned int type);
            void            Link(unsigned int vShader, unsigned int fShader);

            std::pair<std::string, std::string> ParserShaderFile(const char* shader_source);
        private:
            unsigned int                m_sProgram;
    };
}


#endif //SHADER_H_