#pragma once

#include <glm/glm.hpp>

enum shapeID{
  sphere = 0,
  box = 1,
  plane = 2,
};

struct Shape{
  virtual ~Shape(){} ;
};

struct Sphere : public Shape{
  glm::vec3 center ; 
  float radius ;
};

struct Box : public Shape{
    glm::vec3 center ;
    glm::vec3 min_coords = glm::vec3{FLT_MAX}; 
    glm::vec3 max_coords = glm::vec3{-FLT_MAX};
};
  

struct Plane : public Shape{
  glm::vec3 normal ;
  float offset ; 
};
