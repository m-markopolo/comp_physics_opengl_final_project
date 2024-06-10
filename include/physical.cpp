#include "physical.hpp"
#include "collisions.hpp"



Physical_Entity::Physical_Entity(external_filenames f_name,
                                 shapeID shape, 
                                 glm::vec3 pos_0 , glm::vec3 vel_0 , glm::vec3 acc_0, float i_m) 
: Entity(f_name), 
  p(std::move(pos_0), std::move(vel_0), std::move(acc_0)),
  p_shape(get_shape(*this, shape))
  {
  set_particle_properties(std::move(pos_0), std::move(vel_0), std::move(acc_0)) ; 
  p.set_mass(i_m); 
}

glm::vec3 Physical_Entity::get_pos_after(float time ) {
  p.integrate(time);
  return p.get_pos();
}

void Physical_Entity::recalculate_position_and_set_mvp(glm::mat4 const& view_matrix, float time, float scale ) {
  set_mvp_and_set_scale(view_matrix, get_pos_after(time), scale); 
}

void Physical_Entity::set_pos(glm::vec3 pos){
  p.set_prop(std::move(pos)) ;
}



void Physical_Entity::set_particle_properties(glm::vec3 x, glm::vec3 v ,glm::vec3 a ,
    float d,  float i_m ){
  p.pos = x ;
  p.vel= v ;
  p.acc = a ;
  p.damp = d ;
  p.inverse_mass = i_m;

}

bool in_interval(float x, float x_min, float x_max ){
  return x_min <= x <= x_max ; 
}

std::optional<Contact> Physical_Entity::collides_with(Physical_Entity const * const other) const{
  return collide(p_shape, other->p_shape) ;
}
