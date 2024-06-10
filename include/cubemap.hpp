#ifndef CUBEMAP_H
#define CUBEMAP_H


#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "mesh.hpp"
#include "shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Cubemap{

    public:

    std::vector<std::string> faces  ;

    std::vector<float> skyboxVertices = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


        Cubemap( std::vector<std::string> f ){ faces = f ;  } 


        

        unsigned int loadCubemap(){
            unsigned int textureID, skyboxVAO, skyboxVBO ;

            glGenVertexArrays(1, &skyboxVAO ) ;  
            glGenTextures(1, &textureID ) ; 
            glGenBuffers(1, &skyboxVBO ) ; 

            glBindVertexArray( skyboxVAO ) ; 
            glBindTexture( GL_TEXTURE_CUBE_MAP, textureID ); 

            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * skyboxVertices.size(), &skyboxVertices[0], GL_STATIC_DRAW ) ; 

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0 ) ;
            glEnableVertexAttribArray(0) ; 

            glBindBuffer( GL_ARRAY_BUFFER, skyboxVBO ) ;

            int width, height, nrChannels ; 

        for (unsigned int i = 0 ; i < faces.size() ; ++i ){

            unsigned char *data = stbi_load( faces[i].c_str(), &width, &height, &nrChannels, 0 )  ;

            if (data){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                        );
                stbi_image_free(data) ; 

            
            }else{
                std::cerr << "Cubemap tex failed to load at path: " << faces[i] <<  "\n" ; 
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


        glDepthMask( GL_FALSE ) ;

        
        glBindVertexArray(skyboxVAO);
        

        return textureID;
    }  


    void Draw(){


        glDepthFunc(GL_LEQUAL);  // change 
        glDepthMask(GL_FALSE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);  // change 
        glDepthMask(GL_TRUE); 

    }

};

#endif
