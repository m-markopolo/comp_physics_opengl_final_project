#version 330 core

out vec4 FragColor ;
in vec3 Normal ; 
in vec3 FragPos ; 

uniform vec3 object_color ;
uniform vec3 light_color ;
uniform vec3 light_pos ;

void main(){

  float ambientStr = 0.1 ; 
  vec3 ambient = ambientStr * light_color ; 

  vec3 lightDir = normalize(light_pos - FragPos) ;

  vec3 norm = normalize(Normal) ;
  float diff = max(dot(norm, lightDir), 0.0) ;

  vec3 diffuse = diff * light_color ; 
  vec3 result = ( ambient + diffuse ) * object_color ; 

  FragColor = vec4(result, 1.0 ) ;
}
