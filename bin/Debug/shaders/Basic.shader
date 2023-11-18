#shader VertextShader

#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

out vec2 TexCoord;
out vec3 Normal;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    TexCoord = a_TexCoord;
    Normal = a_Normal;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos, 1.0f);
}

#shader FragmentShader
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_Repeat;

void main()
{
    FragColor = texture(u_Texture, TexCoord * u_Repeat);
}