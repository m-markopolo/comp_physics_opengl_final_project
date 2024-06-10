#include "collisions.hpp"
#include "physical_contact.hpp"
#include "physical.hpp"
#include <algorithm>
#include <optional>



Box* get_aabb_from_ent(Physical_Entity const& ent ){

  Model const& model  = ent.m_mesh_model ;
  auto* result = new Box ; 

  std::for_each(model.meshes.begin(), model.meshes.end(), [&](Mesh mesh){
    std::for_each(mesh.vertices.begin(), mesh.vertices.end(), [&](Vertex v){
      glm::vec3 temp = v.Position + ent.p.pos ; 
      std::transform(&temp.x, &temp.z + 1, &result->max_coords.x, &result->max_coords.x, 
                     [](float v_coord, float m_coord) {return std::max(v_coord, m_coord);});
      std::transform(&temp.x, &temp.z + 1, &result->min_coords.x, &result->min_coords.x, 
                     [](float v_coord, float m_coord) {return std::min(v_coord, m_coord);});
    });
  });
  result->center = result->max_coords - result->min_coords ; 
  return result ; 
}

Sphere* get_sphere(Physical_Entity const& x){
  auto* result = new Sphere ; 

  Box* box = get_aabb_from_ent(x) ;
  result->center = box->max_coords - box->min_coords;
  result->radius  = length(result->center); 
  return result ; 
}

Box* get_aabb(Physical_Entity const& x){
  return get_aabb_from_ent(x)  ;
}

glm::vec3 get_normal_in(int axis){
  switch (axis){
    case 0 :{
      return glm::vec3{1,0,0} ;
    }
    default:
    [[fallthrough]] ; 
    case 1 :{
      return glm::vec3{0,1,0} ;
    }
    case 2 :{
      return glm::vec3{0,0,1} ;
    }
  }
}
// the plane has to be aligned with any of the xy,zx, ... planes, and have zero thickness.
Plane* get_plane(Physical_Entity const& x){
  auto* results = new Plane ; 
  Box* box = get_aabb_from_ent(x) ;
  glm::vec3 temp = box->max_coords - box->min_coords ;
  auto it = std::find_if(&temp.x, &temp.z + 1, 
               [](float x) -> bool {return fabs(x) < 0.1 ;}) ;
  if(it != &temp.z + 1 ){
    auto zero_axis = std::distance(&temp.x, it); 
    results->normal = get_normal_in(zero_axis) ;
    results->offset = *(&box->min_coords.x + zero_axis) ;
    return results ;
  }
  return nullptr ; 
}

Shape* get_shape( Physical_Entity const& x, shapeID ID  ){
  switch (ID) {
    
    default:
    [[fallthrough]] ;
    case sphere:{
      return get_sphere(x) ;
    }
    case box :{
      return get_aabb(x) ;
    }
    case plane:{
      return get_plane(x) ;
    }

  }
}
std::optional<Contact> collide(Sphere* a, Sphere* b ){
  using namespace glm ; 
  vec3 midline = b->center - a->center; 
  if(float mag =  length(midline); mag < b->radius + a->radius ){

    vec3 normal = normalize(midline);
    
    return Contact(
      a->center + midline * 0.5f,
      normal,
      a->radius + b->radius - mag,
      a,
      b
      );
  } 
  return std::nullopt ;
}
std::optional<Contact> collide(Sphere* sphere, Plane* plane ){

  // std::cerr << plane->normal << ": plane normal \n";
  // std::cerr << sphere->center << ": sphere center \n";
  if( float center_distance_from_plane = dot(plane->normal,sphere->center) - plane->offset ;
     fabs(center_distance_from_plane) < sphere->radius ){


  return Contact(
      sphere->center - plane->normal* ( center_distance_from_plane ), 
      plane->normal,
      center_distance_from_plane - sphere->radius,
      sphere,
      nullptr
  );
  } 
  return std::nullopt ; 
}

std::optional<Contact> collide(Shape* a, Shape* b){
  
  if(auto* s = dynamic_cast<Sphere*> (a) ; s ){
    if(auto* s2 = dynamic_cast<Sphere*> (b) ; s2 ){
      return collide(s,s2) ;
    }else if(auto* s2 = dynamic_cast<Plane*> (b) ; s2 ){
      return collide(s,s2) ;
    }
    //TODO add box 
  }
  return std::nullopt ;  
}

