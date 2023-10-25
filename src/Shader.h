#ifndef SHADER_H_
#define SHADER_H_

namespace GL
{
    class Shader
    {
        public:
            enum class ShaderType
            {
                NONE = 0,
                VERTEX,
                FRAGMENT
            };

            explicit Shader(const char* shader_source);
            ~Shader();
            void Bind();
            void UnBind();

        private:
            unsigned int    Compile(const char* shader, unsigned int type);
            void            Link(unsigned int vShader, unsigned int fShader);

            std::pair<std::string, std::string> ParserShaderFile(const char* shader_source);
        private:
            unsigned int m_sProgram;
    };
}


#endif //SHADER_H_