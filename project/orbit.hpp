#ifndef ORBIT_HPP
#define ORBIT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "set_up.hpp"


class Orbit_Calculator {

public: 
  struct Orbit_Data {
    float theta;
    float w;
    float r;
    glm::vec3 m_pos;
    Orbit_Data(glm::vec3 pos ,double w);
    Orbit_Data(glm::vec3 pos );

  };
 private:

  Orbit_Data m_satellite_data;

 public:
    
  Orbit_Calculator(glm::vec3 const &,  double w) ;
  glm::vec3 get_pos_after( double time_elapsed_since_last_iteration);

 private:
  glm::vec3 revolve_for(Orbit_Data &data,  double time_from_last_iter);
};

#endif
