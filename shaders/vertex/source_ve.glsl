#version 330 core

layout (location = 0) in vec3 aPos ; 

uniform mat4 view ;
uniform mat4 model ;
uniform mat4 projection ;
uniform mat4 rotate ;

uniform vec3 position ;
// uniform vec3 viewer_position;

out vec3 FragPos ; 

void main(){

  mat4 newmodel = rotate * model  ;
  // vec3 aPos = vec3( rotate * vec4( aPos, 1.0 ) ) ;

  gl_Position = projection * view * model * vec4( aPos + position, 1.0)  ;

  FragPos = vec3( model * vec4( aPos + position , 1.0 ));

}
