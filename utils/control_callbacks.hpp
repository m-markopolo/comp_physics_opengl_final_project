#ifndef CONTROL_CALLBACKS_HPP
#define CONTROL_CALLBACKS_HPP


#include <string>
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp>

GLFWwindow* create_window_init_glad( int width, int height, std::string const & name );

void move_the_light(GLFWwindow *win, glm::vec3 &pos) ;
void change_light_color(GLFWwindow *win, glm::vec3 &color) ;

#endif
