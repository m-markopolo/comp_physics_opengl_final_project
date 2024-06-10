
#include <glad/glad.h>

#include "control_callbacks.hpp"

#include <glm/common.hpp>
#include <string>
#include <GLFW/glfw3.h> 
#include <iostream>


GLFWwindow* create_window_init_glad( int width, int height, std::string const & name ){

    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str() , NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << "\n" ;
        return nullptr;
    }    

    return window ; 
}

void move_the_light(GLFWwindow *win, glm::vec3 &pos) {

  float d = 0.05 ; 
  if (glfwGetKey(win, GLFW_KEY_N) == GLFW_PRESS)
    pos += glm::vec3(d, 0.0f, 0.0f);
  if (glfwGetKey(win, GLFW_KEY_M) == GLFW_PRESS)
    pos += glm::vec3(-d, 0.0f, 0.0f);

  if (glfwGetKey(win, GLFW_KEY_K) == GLFW_PRESS)
    pos += glm::vec3(0.0f, d, 0.0f);
  if (glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS)
    pos += glm::vec3(0.0f, -d, 0.0f);

  if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS)
    pos += glm::vec3(0.0f, 0.0f, d);
  if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
    pos += glm::vec3(0.0f, 0.0f, -d);
}
void change_light_color(GLFWwindow *win, glm::vec3 &color) {

  
  float d = 0.05 ; 
  if (glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS)
    color += glm::vec3(d, 0.0f, 0.0f);
  if (glfwGetKey(win, GLFW_KEY_2) == GLFW_PRESS)
    color += glm::vec3(-d, 0.0f, 0.0f);

  if (glfwGetKey(win, GLFW_KEY_3) == GLFW_PRESS)
    color += glm::vec3(0.0f, d, 0.0f);
  if (glfwGetKey(win, GLFW_KEY_4) == GLFW_PRESS)
    color += glm::vec3(0.0f, -d, 0.0f);

  if (glfwGetKey(win, GLFW_KEY_5) == GLFW_PRESS)
    color += glm::vec3(0.0f, 0.0f, d);
  if (glfwGetKey(win, GLFW_KEY_6) == GLFW_PRESS)
    color += glm::vec3(0.0f, 0.0f, -d);
  color = glm::clamp(color, 0.f, 1.f ) ;
}
