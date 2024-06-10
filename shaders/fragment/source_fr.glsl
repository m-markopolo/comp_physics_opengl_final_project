#version 330 core 
out vec4 FragColor ; 
in vec3 FragPos ; 

uniform vec3 source_color ; 

void main(){
  FragColor = vec4(source_color , 1.0) ;
     
}


