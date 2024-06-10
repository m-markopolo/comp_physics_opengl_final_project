#ifndef MESH_H
#define MESH_H

#include "GL/glew.h" // include GLEW and new version of GL on Windows
#include <GL/gl.h>
#include <GL/glext.h>

#include <vector>
#include <string>


struct Vertex{
  glm::vec3 Position; 
  glm::vec3 Normal; 
  glm::vec2 TexCoords; 
};

struct Texture{
  GLuint id ;
  std::string type ; 
  std::string path ; 
};

class Mesh{


  public:

    unsigned int vao = 0
      , vbo, ebo ;

    std::vector<Vertex>   vertices ; 
    std::vector<GLuint>   indices ; 
    std::vector<Texture>   textures ; 

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint>   indices, std::vector<Texture> textures ) { 


      this->vertices =  vertices ; 
      this->indices  =  indices  ; 
      this->textures =  textures ; 

      setupMesh(); 

    }



    
    void setupMesh(){ 

     glGenVertexArrays(1, &vao) ; 
     glGenBuffers(1, &vbo);
     glGenBuffers(1, &ebo);

     glBindVertexArray(vao) ; //Bind this first, as every bindbuffer call after this will bind the vbo to the vao.

     glBindBuffer(GL_ARRAY_BUFFER , vbo  );
     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex) , &vertices[0], GL_STATIC_DRAW );

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ebo  );
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( GLuint ) , &indices[0], GL_STATIC_DRAW );

     glEnableVertexAttribArray(0); 
     glVertexAttribPointer(
                           0,
                           3,
                           GL_FLOAT, 
                           GL_FALSE, 
                           sizeof(Vertex), 
                           (void*)0 
                           );


     glEnableVertexAttribArray(1); 
     glVertexAttribPointer(
                           1,
                           3,
                           GL_FLOAT, 
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex, Normal)
                           );

     glEnableVertexAttribArray(2); 
     glVertexAttribPointer(
                          2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void*)offsetof(Vertex, TexCoords)
                          );



     glBindVertexArray(0); //unbind the vao

    }

    void Draw( Shader &shader){

      GLuint num_diffuse = 1 ;
      GLuint num_specular = 1 ;

      for (GLuint idx_tex = 0; idx_tex < textures.size() ; ++idx_tex ){

        glActiveTexture(GL_TEXTURE0 + idx_tex ) ;  // The addition gives an offset 
                                                   // leading to the next element 

        std::string  number , 
                     name = textures[ idx_tex ].type ; 

        if ( "texture_diffuse" ==  name ) 
          number = std::to_string( num_diffuse++ ) ; // ++i : increment and return
                                                     // i++ : return and increment
        else if( "texture_specular" == name ) 
          number = std::to_string( num_specular++ ) ;

        shader.setInt( ("material." + name + number ).c_str(), idx_tex ) ; 
        glBindTexture(GL_TEXTURE_2D, textures[ idx_tex ].id ); 
      }
      glActiveTexture(GL_TEXTURE0) ; 

      glBindVertexArray(vao) ; 
      glDrawElements( GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 ); 
      glBindVertexArray(0) ; // unbind  the vao 
    } 

};


#endif
