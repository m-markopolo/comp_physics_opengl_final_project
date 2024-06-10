#include <algorithm>
#include <iostream> 
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include "definitions.hpp"

#ifdef DEBUG_MODE
void print(glm::vec3 const& vec){
  std::for_each(&vec.x, &vec.z + 1, [](float x ){std::cout << x << ','; });
  std::cout << '\n' ;
}
#endif
