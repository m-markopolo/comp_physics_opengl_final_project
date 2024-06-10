#version 330 core

out vec4 FragColor ;
in vec3 Normal ; 
in vec3 FragPos ; 

uniform vec3 object_color ;
uniform vec3 viewer_position;
uniform vec3 light_color ;
uniform vec3 light_dir ;
uniform mat4 rotate;

void main(){

  float ambientStr = 0.1 ; 
  vec3 ambient = ambientStr * light_color ; 

 
  vec3 norm = vec3( rotate * vec4(normalize(Normal), 1.0)) ;
  float diff = max( dot(norm, light_dir ), 0.0) ;

  vec3 diffuse = diff * light_color ; 
  vec3 result = ( ambient + diffuse ) * object_color ; 

  FragColor = vec4(result, 1.0 ) ;
}
