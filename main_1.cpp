#include <glad/glad.h>
//--------------------------------------------------  
//--------------------------------------------------  
#include <functional>
#include <iostream>
#include <random>
#include <string>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "include/controls.hpp"
#include "include/mesh.hpp"
#include "include/model.hpp"
#include "include/set_up.hpp"
#include "include/shader.hpp"

#include "project/orbit.hpp"

#include "control_callbacks.hpp"



void move_the_light(GLFWwindow *win, glm::vec3 &pos) ;

int constexpr width = 1400, height = 720;
float xpos_previous = width/2.  , ypos_previous = height/2. ;
bool first_time_entered_the_window = true;

GLFWwindow *window = create_window_init_glad(width, height, "Finally");
Camera cam(window, glm::vec3(0.0f, -10.0f, 2.0f));

void cursor_pos_callback(GLFWwindow *win, double xpos, double ypos);

int main(int argc, char *argv[]) {
 external_filenames f_names_obj = {" ",
   "shaders/vertex/object_ve_pos_light.glsl",
   "shaders/fragment/object_fr_pos_light.glsl"};

  Entity rubber_duck("obj/rubber_duck.obj", f_names_obj.vert, f_names_obj.frag);
  Entity object("obj/dimorphos.obj",f_names_obj.vert,f_names_obj.frag);
  Entity light_source("obj/cube.obj",
                            "shaders/vertex/source_ve.glsl",
                            "shaders/fragment/source_fr.glsl");
  TheSkybox skybox("textures/skybox",
                            "shaders/vertex/skybox_ve.glsl",
                            "shaders/fragment/skybox_fr.glsl");


  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


  double constexpr R_sat = 1.19 ; 

  auto object_pos = glm::vec3{0.0, 0.0, 0.0} ;
  auto satellite_pos =  glm::vec3{R_sat, 0.0, 0.0};
  auto light_source_pos =  glm::vec3{0.0, 0.0, R_sat };

    

  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_CULL_FACE);  

  double time_since_last_frame = glfwGetTime() ;
  double time_in_last_frame = time_since_last_frame  ;

  glm::vec3 object_color = {1, 1.0, 1.0} ;
  glm::vec3 light_color = object_color ;

  while (!glfwWindowShouldClose(window)) {


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = cam.get_view_matrix();
    draw_skybox(&skybox, view ) ;
    cursor_pos_callback(window, xpos_previous, ypos_previous);
    cam.translate_camera();

    
    time_since_last_frame = glfwGetTime() - time_in_last_frame ; 
    time_in_last_frame = glfwGetTime() ; 
    

    float level_scale = 1.f;

    move_the_light(window, light_source_pos ) ;
    change_light_color(window, light_color) ;

    using property_vec_t = std::vector<std::pair<std::string, glm::vec3>> ; 
    using property_mat_t = std::vector<std::pair<std::string, glm::mat4>> ; 

    draw_entity(&object, view, object_pos, level_scale) ;

    object.set_properties(
      property_vec_t{
                   {"light_color", light_color},
                   {"object_color", object_color},
                   {"light_pos", light_source_pos}
      });

    object.draw();


    draw_entity(&rubber_duck, view, satellite_pos, level_scale) ;

    rubber_duck.set_properties(
      property_vec_t{
      {"light_color", light_color},
      {"light_pos",    light_source_pos},
      {"object_color", object_color}
      }
    );

    rubber_duck.draw() ; 


    draw_entity(&light_source, view, light_source_pos, level_scale );
    light_source.set_properties(
      property_vec_t{
      {"light_color", light_color},
      {"source_color", light_color},
      {"position", light_source_pos}
      }
    );
    light_source.draw() ; 

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}




void cursor_pos_callback(GLFWwindow *win, double xpos, double ypos) {
  if (first_time_entered_the_window == true) {
    xpos_previous = xpos;
    ypos_previous = ypos;
    first_time_entered_the_window = false;
  }

  float xoffset = xpos - xpos_previous;
  float yoffset = ypos - ypos_previous;

  xpos_previous = xpos;
  ypos_previous = ypos;

  cam.rotate(xoffset, yoffset);
}


