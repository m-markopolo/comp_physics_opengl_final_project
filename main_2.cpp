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
#include "definitions.hpp"

#include "orbit.hpp"

#include "control_callbacks.hpp"



void move_the_light(GLFWwindow *win, glm::vec3 &pos) ;

int constexpr width = SCR_WIDTH, height = SCR_HEIGHT;
float xpos_previous = width/2.  , ypos_previous = height/2. ;
bool first_time_entered_the_window = true;

GLFWwindow *window = create_window_init_glad(width, height, "Finally");
Camera cam(window, glm::vec3(0.0f, -10.0f, 2.0f));

void cursor_pos_callback(GLFWwindow *win, double xpos, double ypos);

int main(int argc, char *argv[]) {

  Entity satellite("obj/dimorphos.obj",
                            "shaders/vertex/object_ve.glsl",
                            "shaders/fragment/object_fr.glsl"
                            );
  Entity object("obj/didymain2019.obj",
                            "shaders/vertex/object_ve.glsl",
                            "shaders/fragment/object_fr.glsl"
                            );
  Entity light_source("obj/cube.obj",
                            "shaders/vertex/source_ve.glsl",
                            "shaders/fragment/source_fr.glsl"
                      );
  TheSkybox skybox("textures/skybox",
                            "shaders/vertex/skybox_ve.glsl",
                            "shaders/fragment/skybox_fr.glsl"
                      );


  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


  double constexpr R_sat = 1.19 ; 
  glm::vec3 constexpr light_source_pos =  glm::vec3{R_sat, 0.0, 0.0 };

  auto object_pos = glm::vec3{0.0, 0.0, 0.0} ;
  auto satellite_pos =  glm::vec3{R_sat, 0.0, 0.0};


  double constexpr w_satellite = 2. * M_PI / 12.  ;
  double constexpr w_object = 2. * M_PI / 2.3;

  double theta_obj = 0.0 ; 
  double theta_satellite = 0.0 ; 
    

  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_CULL_FACE);  

  double time_since_last_frame = glfwGetTime() ;
  double time_in_last_frame = time_since_last_frame  ;

  Orbit_Calculator orbit_calc(satellite_pos, w_satellite ) ;


  while (!glfwWindowShouldClose(window)) {


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = cam.get_view_matrix();
    skybox.use() ; 
    skybox.set_view(view) ;
    skybox.draw_skybox() ; 

    cursor_pos_callback(window, xpos_previous, ypos_previous);
    cam.translate_camera();

    
    time_since_last_frame = glfwGetTime() - time_in_last_frame ; 
    time_in_last_frame = glfwGetTime() ; 
    


    glm::vec3 object_color = {1, 1.0, 1.0} ;
    glm::vec3 light_color = object_color ;


    using property_vec_t = std::vector<std::pair<std::string, glm::vec3>> ; 
    using property_mat_t = std::vector<std::pair<std::string, glm::mat4>> ; 


    object.use();
    object.set_mvp( view, object_pos ) ;


    theta_obj += w_object * time_since_last_frame ; 

    object.set_properties(
      property_mat_t{
        {"rotate",
        glm::rotate(glm::mat4(1.0f), 
                     static_cast<float>(theta_obj),
                    glm::vec3(0, 0, 1)) 
            } 
      }
      );

    object.set_properties(
      property_vec_t{
                   {"light_color", light_color},
                   {"object_color", object_color},
                   {"light_dir", light_source_pos}
      });

    object.draw();


    satellite.use();
    satellite_pos = orbit_calc.get_pos_after(time_since_last_frame);
    satellite.set_mvp( view, satellite_pos) ;

    // theta_satellite += w_satellite * time_since_last_frame ; 
    theta_satellite += w_satellite * time_since_last_frame ; 

      satellite.set_properties(
      property_mat_t{
      {"rotate",
        glm::rotate(glm::mat4(1.0f), 
                     static_cast<float>(theta_satellite),
                    glm::vec3(0, 0, 1)) 
          }
      }
      );
    satellite.set_properties(
      property_vec_t{
      {"light_color", light_color},
      {"light_dir",    light_source_pos},
      {"object_color", object_color}
      }
    );

    satellite.draw() ; 



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


