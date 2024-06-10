#pragma once 

#include <vector> 
#include "glm/vec3.hpp"
#include "shapes.hpp"

class Physical_Entity ;

struct Contact{
  Contact(glm::vec3 p, glm::vec3 n, float depth, 
  Shape const * const  a , Shape const * const b ) 
    : point(std::move(p)), normal(std::move(n)), depth(depth), first(a), second(b){}
  glm::vec3  point  ;
  glm::vec3  normal ;
  float      depth  ;
  Shape const * const  first ; 
  Shape const * const second ;
 
void adjust_positions(Physical_Entity * a, Physical_Entity * b  );
void adjust_velocities(Physical_Entity * a, Physical_Entity * b );
void resolve_contact(Physical_Entity * a, Physical_Entity * b );
};

void find_contacts(std::vector<Physical_Entity*> & ents);
