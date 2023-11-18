#ifndef GL_UTILS_HPP_
#define GL_UTILS_HPP_

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

namespace GL
{
    struct POS
    {
        float x;
        float y;
        float z;
        POS(float a, float b, float c)
            :x(a),y(b),z(c){}

        POS(const POS& rhs)
            : x(rhs.x), y(rhs.y), z(rhs.z){}
    };

    struct TEX
    {
        float x;
        float y;

        TEX(float a, float b)
            :x(a),y(b){}

        TEX(const POS& rhs)
            : x(rhs.x), y(rhs.y){}
    };

    struct NORM
    {
        float x;
        float y;
        float z; 

        NORM(float a, float b, float c)
            :x(a),y(b),z(c){}

        NORM(const POS& rhs)
            : x(rhs.x), y(rhs.y), z(rhs.z){}
    };

    class BufferLayout
    {
    public:
        POS Pos;
        TEX Tex;
        NORM Norm;

        BufferLayout()
        : Pos{0.0f,0.0,0.0f}, Tex{0.0f, 0.0,}, Norm{0.0f, 0.0f,1.0f}{}

        BufferLayout(const POS& pos, const TEX& tex, const NORM& normalize)
            : Pos(pos), Tex(tex), Norm(normalize)
        {}

        BufferLayout(const BufferLayout& lay)
            : Pos(lay.Pos), Tex(lay.Tex), Norm(lay.Norm){}

        BufferLayout(const BufferLayout&& lay)
        : Pos(std::move(lay.Pos)), Tex(std::move(lay.Tex)), Norm(std::move(lay.Norm)){}
    };

    // XOY平面， Z > 0
    static std::vector<BufferLayout> g_vecGet{
        
        { POS(  0.5f, 0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS( -0.5f, 0.5f, 0.5f), TEX( 0.0f, 1.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS( -0.5f,-0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS( -0.5f,-0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS(  0.5f,-0.5f, 0.5f), TEX( 1.0f, 0.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS(  0.5f, 0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  0.0f, 1.0f ) },
        { POS( -0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS(  0.5f, 0.5f,-0.5f), TEX( 0.0f, 1.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS(  0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS(  0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS( -0.5f,-0.5f,-0.5f), TEX( 1.0f, 0.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS( -0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  0.0f,-1.0f ) },
        { POS(  0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f, 0.5f, 0.5f), TEX( 0.0f, 1.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f,-0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f,-0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f,-0.5f,-0.5f), TEX( 1.0f, 0.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f, 0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f, 0.5f,-0.5f), TEX( 0.0f, 1.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f,-0.5f, 0.5f), TEX( 1.0f, 0.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS( -0.5f, 0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM( -1.0f,  0.0f, 0.0f ) },
        { POS(  0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS( -0.5f, 0.5f,-0.5f), TEX( 0.0f, 1.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS( -0.5f, 0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS( -0.5f, 0.5f, 0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS(  0.5f, 0.5f, 0.5f), TEX( 1.0f, 0.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS(  0.5f, 0.5f,-0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f,  1.0f, 0.0f ) },
        { POS(  0.5f,-0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f, -1.0f, 0.0f ) },
        { POS( -0.5f,-0.5f, 0.5f), TEX( 0.0f, 1.0f ), NORM(  0.0f, -1.0f, 0.0f ) },
        { POS( -0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f, -1.0f, 0.0f ) },
        { POS( -0.5f,-0.5f,-0.5f), TEX( 0.0f, 0.0f ), NORM(  0.0f, -1.0f, 0.0f ) },
        { POS(  0.5f,-0.5f,-0.5f), TEX( 1.0f, 0.0f ), NORM(  0.0f, -1.0f, 0.0f ) },
        { POS(  0.5f,-0.5f, 0.5f), TEX( 1.0f, 1.0f ), NORM(  0.0f, -1.0f, 0.0f ) }
    };

}

#endif //GL_UTILS_HPP_