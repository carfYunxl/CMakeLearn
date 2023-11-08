#shader VertextShader

#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0f);
}

#shader FragmentShader
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 u_LightObjColor;

void main()
{
    FragColor = vec4( u_LightObjColor, 1.0 );
}