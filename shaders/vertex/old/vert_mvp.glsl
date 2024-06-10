#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


out vec2 TexCoord;
out vec3 NormCoord;

void main()
{
//    ourColor = aColor;
   TexCoord = aTexCoord;
   NormCoord = aNormals ; 
   gl_Position = projection*view*model*vec4(aPos,1.0);

}
