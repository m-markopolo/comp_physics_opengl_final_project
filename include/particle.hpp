#pragma once 

#include <glm/fwd.hpp>
#include <glm/common.hpp>
#include "definitions.hpp"



struct particle{

  glm::vec3 pos ;  // position
  glm::vec3 vel = {0,0,0};  // velocity
  glm::vec3 acc = {0,0, -constants::G };  // acceleration
  float damp= 0.998 ; // damping factor 
  float inverse_mass = 0. ; 
  

public : 

  void set_mass(float i_m ) ; 
  void set_prop(glm::vec3 x ) ; 
  void set_prop(glm::vec3 x,  glm::vec3 a ) ; 
  void set_prop(glm::vec3 x, glm::vec3 v, glm::vec3 a ) ; 

  particle(glm::vec3 x, glm::vec3 v = {0,0,0}, glm::vec3 a = {0,0, -constants::G }, 
                   float d = 0.999, float i_m= 0. );
  void integrate( float time);

  float get_inverse_mass() const  ;
  glm::vec3 get_pos() const ; 
  glm::vec3 get_acc() const ; 
  glm::vec3 get_vel() const ; 


};

