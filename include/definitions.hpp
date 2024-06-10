#pragma once 

#include <vector>
#include <string>
#include <glm/fwd.hpp>

#define SCR_WIDTH 1920 
#define SCR_HEIGHT 1080
#define LEVEL_SCALE 1.0f

#define DEBUG_MODE

namespace constants{
  constexpr float G = 1 ; 
  constexpr float lower_vel_limit = 2 ;
}
using vec3_property_t  =  std::vector<std::pair<std::string, glm::vec3>> ; 
using mat4_property_t  =  std::vector<std::pair<std::string, glm::mat4>> ;
