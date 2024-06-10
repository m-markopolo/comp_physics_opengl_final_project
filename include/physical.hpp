#pragma once

#include "physical_contact.hpp"
#include <optional>
#include "set_up.hpp"
#include "particle.hpp"
#include "shapes.hpp"

inline auto& operator <<(std::ostream & ostr, glm::vec3 vec ){
  for(int i = 0 ;i < 3 ; ++i){
    ostr << vec[i] << " " ;
  }
  return ostr << " " ;
}

class Physical_Entity : public Entity {
public: 
  particle p ; 
  Shape* p_shape = nullptr ;
  Physical_Entity(external_filenames f_name, 
                  shapeID shape = sphere,
                  glm::vec3 pos_0 = {0,0,0},
                  glm::vec3 vel_0 = {0,0,0},
                  glm::vec3 acc_0 = {0,0,-constants::G},
                  float i_m = 0.
                  ); 
  void recalculate_position_and_set_mvp(glm::mat4 const & view_matrix, float time, float scale = LEVEL_SCALE) ;
  void set_pos(glm::vec3 pos ) ;
  void set_particle_properties(glm::vec3 x, glm::vec3 v ,glm::vec3 a ,
    float d = 0.998, float i_m= 0. );
                   
  std::optional<Contact> collides_with(Physical_Entity const * const  other) const ; 
  ~Physical_Entity(){
    if(p_shape) 
      delete(p_shape);  //this is retarded 
  }

private: 
  glm::vec3 get_pos_after(float time ) ;
};



