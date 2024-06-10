#version 330 core
layout (location = 0) in vec3 aPos ; 
layout (location = 1) in vec3 aNormal ; 
layout (location = 2) in vec2 aTexCoords ; 

uniform mat4 view ;
uniform mat4 model ;
uniform mat4 projection ;
uniform mat4 rotate;
uniform mat4 ls_trans ;

uniform vec3 viewer_position;


out VS_OUT{
  vec3 Normal ; 
  vec3 FragPos ; 
  vec2 TexCoords ; 
  vec4 FragPosInLightSpace ; 
}vs_out ; 

void main(){


  mat4 newmodel = rotate * model ; 

  vec3 aPos = vec3(rotate * vec4(aPos, 1.0) )  ;


  vs_out.FragPos = vec3( model * vec4(aPos, 1.0 )) ;
  vs_out.Normal = mat3(inverse(transpose( model))) * vec3(rotate * vec4(aNormal, 1.0 )) ;
  vs_out.TexCoords = aTexCoords ; 
  vs_out.FragPosInLightSpace =  ls_trans * vec4(vs_out.FragPos, 1.0) ; 

  gl_Position = projection *  view * vec4(vs_out.FragPos, 1.0)  ;

}

