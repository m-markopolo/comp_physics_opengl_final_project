#include "particle.hpp"

#include "definitions.hpp"

particle::particle(glm::vec3 x, glm::vec3 v , glm::vec3 a , 
                   float d , float i_m):
      pos(x),vel(v),acc(a),
       damp(d), inverse_mass(i_m) {} 

glm::vec3 constexpr update_position_using_newton_euler(glm::vec3 x, glm::vec3 v, float time ){
  return x + v * time ;
}
glm::vec3 constexpr update_velocity_using_newton_euler(glm::vec3 v, glm::vec3 a, float time ){
  return v + a * time ;
}

void particle::integrate(float time){
  pos = update_position_using_newton_euler(pos, vel, time) ;
  vel = update_velocity_using_newton_euler(vel * damp , acc, time) ;
}

glm::vec3 particle::get_pos() const { 
  return pos ; 
}
glm::vec3 particle::get_vel() const { 
  return vel ; 
}
glm::vec3 particle::get_acc() const { 
  return acc ; 
}
float particle::get_inverse_mass() const { 
  return inverse_mass ; 
}
using namespace glm; 
void particle::set_mass(float m) { 
  inverse_mass = m ;
}
void particle::set_prop(vec3 x) { 
  pos = std::move(x) ;
}
void particle::set_prop(vec3 x, vec3 v) { 
  pos = std::move(x) ;
  vel = std::move(v) ;
}
void particle::set_prop(vec3 x, vec3 v, vec3 a) { 
  pos = std::move(x) ;
  vel = std::move(v) ;
  acc = std::move(a) ;
}
