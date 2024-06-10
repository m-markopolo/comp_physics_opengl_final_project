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

#include "controls.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "set_up.hpp"
#include "shader.hpp"
#include "physical.hpp"
#include "definitions.hpp"

#include "control_callbacks.hpp"



int constexpr width = SCR_WIDTH, height = SCR_HEIGHT;
float xpos_previous = width/2.  , ypos_previous = height/2. ;
bool first_time_entered_the_window = true;

GLFWwindow *window = create_window_init_glad(width, height, "Finally");
auto constexpr init_pos =  glm::vec3(0.0f, -5.0f, 2.0f);
Camera cam(window, init_pos);


void cursor_pos_callback(GLFWwindow *win, double xpos, double ypos);
int main(int argc, char *argv[]) {


 TheSkybox skybox("textures/skybox",
                            "shaders/vertex/skybox_ve.glsl",
                            "shaders/fragment/skybox_fr.glsl");
 external_filenames f_names = {"obj/cube.obj",
                            "shaders/vertex/test_ve.glsl",
                            "shaders/fragment/test_fr.glsl"};

  Physical_Entity player(f_names, shapeID::sphere, init_pos, {0,0,0}, {0,0,-constants::G}, 1. );
  Physical_Entity random_cube(f_names, shapeID::sphere, {0,0,10}, {0,0,0}, {0,0,-constants::G}, 1.);
  Physical_Entity random_cube2(f_names, shapeID::sphere, {0,5,10}, {0,0,0}, {0,0,-constants::G}, 1.);
  Physical_Entity random_cube3(f_names, shapeID::sphere, {4,5,8}, {0,0,0}, {0,0,-constants::G}, 1.);
  Physical_Entity plane({"obj/plain_plane.obj",f_names.vert,f_names.frag}, shapeID::plane, 
                        {0,0,0}, {0,0,0}, {0,0,0}, 0);


  std::vector<Physical_Entity*> ents{&player, &plane, &random_cube, &random_cube2, &random_cube3 } ;

  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_CULL_FACE);  

  double time_since_last_frame = glfwGetTime() ;
  double time_in_last_frame = time_since_last_frame  ;

  while (!glfwWindowShouldClose(window)) {

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    time_since_last_frame = glfwGetTime() - time_in_last_frame ; 
    time_in_last_frame = glfwGetTime() ; 

    draw_skybox(&skybox, cam.get_view_matrix()) ;
    draw_player(&player,  cam,  time_since_last_frame) ;
    glm::mat4 view = cam.get_view_matrix();
    find_contacts(ents);

    draw_entity(&random_cube, view, {}, time_since_last_frame) ;
    random_cube.set_properties(vec3_property_t{{"color", glm::vec3{0.4,0.2,0.4}}}) ;
    draw_entity(&plane, view, {}, time_since_last_frame, 10) ;
    for(int i = 3 ; i < ents.size() ; ++i ){
      auto* ph_ent = ents[i] ;
      draw_entity(ph_ent, view, {}, time_since_last_frame) ;
      ph_ent->set_properties(vec3_property_t{{"color", glm::vec3{1.0,1.0,0.0}}}) ;
    }
    cursor_pos_callback(window, xpos_previous, ypos_previous);
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
