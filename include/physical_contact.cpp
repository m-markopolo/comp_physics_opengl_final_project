  
#include <vector>
#include "physical_contact.hpp"
#include "physical.hpp"
#include "definitions.hpp"




float i_m(Physical_Entity * x) {
  return x ? x->p.get_inverse_mass() : 0  ;
}
glm::vec3 vel(Physical_Entity * x) {
  return x ? x->p.get_vel() : glm::vec3{}  ;
}
void Contact::adjust_positions(Physical_Entity * a, Physical_Entity * b){
  float constexpr c_correction= 0.2 ;
  float constexpr slack = 0.15 ;


  if(i_m(a) + i_m(b) == 0) return ; 
  glm::vec3 correction = glm::max( 
    glm::vec3(depth - slack), 
    c_correction * depth * normal / ( i_m(a) + i_m(b) )
  );

  a->p.pos -= i_m(a) * correction ;
  if(b){
    b->p.pos += i_m(b) * correction ;
  }
}
void Contact::adjust_velocities(Physical_Entity * a, Physical_Entity * b){

  glm::vec3 rv = vel(a) - vel(b) ;

  float projected_vel =  glm::dot(rv, normal)  ;
  if(i_m(a) + i_m(b) == 0) return ; 
  if(projected_vel > 0 ) return ;

  float velocity_from_acc = glm::dot(a->p.get_acc(),  normal) 
   - ((b) ? glm::dot(b->p.get_acc(),  normal) : 0) ; 

  float restitution = (fabs(projected_vel) < constants::lower_vel_limit )  ? 0.f : 1.f ; 
  float j =  - (1 + restitution ) * ( projected_vel - velocity_from_acc )  ;
  j /= i_m(a) + i_m(b) ;

  a->p.vel += normal * i_m(a) * j ;
  if(b){
    b->p.vel -= normal * i_m(b) * j ;
  }

}
void update_shape(Physical_Entity * ent ){
  if( !ent )  return ; 
  if(auto sph = dynamic_cast<Sphere*> (ent->p_shape) ; sph  ){
    sph->center = glm::vec3(ent->get_model() * glm::vec4(ent->p.get_pos(), 1.0)) ;
  }
}
void Contact::resolve_contact(Physical_Entity * a, Physical_Entity * b){
  adjust_positions(a,b) ;   
  adjust_velocities(a,b) ;   
}

void find_contacts(std::vector<Physical_Entity* > & ents) {

  if(ents.size() < 2 ) return ;
  std::for_each(ents.begin(), ents.end(), [](Physical_Entity* ent ){ update_shape(ent); });

  for( int idx1 = 0 ; idx1 < ents.size() ; ++idx1 ){
    for( int idx2 = 0 ; idx2 < ents.size() ; ++idx2 ){
      if (idx1 == idx2 ) continue ;
      auto* i = ents[idx1] ;
      auto* j = ents[idx2] ;
      if( auto result = i->collides_with(j) ; result){
        result->resolve_contact(i,j) ; 
      }
    }
  }
}

