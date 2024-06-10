#include "orbit.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

glm::vec3 Orbit_Calculator::revolve_for(Orbit_Data& data, double time_elapsed_since_last_iteration ) {
  using namespace glm;

  double dtheta = data.w * time_elapsed_since_last_iteration;

  data.theta += dtheta;

  return 
    data.r * vec3(cos(data.theta), sin(data.theta), 0.0) +
    vec3{0, 0, data.m_pos.z };
}

Orbit_Calculator::Orbit_Data::Orbit_Data(glm::vec3 pos, double w_)
    : theta(atan(pos.y / pos.x)),
      r(sqrt(glm::dot(glm::vec2{pos.x, pos.y}, glm::vec2{pos.x, pos.y}))),
      m_pos(std::move(pos)),
      w(w_) {}

Orbit_Calculator::Orbit_Calculator(glm::vec3 const& pos, double w)
    : m_satellite_data(pos, w) {}

glm::vec3 Orbit_Calculator::get_pos_after(double time) {
  return revolve_for(m_satellite_data, time);
}
