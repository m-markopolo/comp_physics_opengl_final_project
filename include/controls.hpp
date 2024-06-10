#ifndef CONTROL_H
#define CONTROL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

class Camera {
 private:
  glm::vec3 pos;               // position vector
  glm::vec3 right, front, up;  // coordinate system
  glm::vec3 world_up;          // world-global up direction
  float yaw, pitch;  // yaw, pitch angles (roll = 0 always for the camera)
  float vel;         // velocity magnitude
  float mouse_sensitivity;
  float t1 = 0.0f, t2, delta_time = 0.0f;
  GLFWwindow * m_win = nullptr ; 

 public:
  Camera(GLFWwindow *win = nullptr,
         glm::vec3 init_pos = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 init_world_up = glm::vec3(0.0f, 0.0f, 1.0f),
         float init_yaw = 90.0f, float init_pitch = 0.0f,
         float init_vel = 1.9f, float init_mouse_sensitivity = 0.05f);

  glm::mat4 get_view_matrix();
  glm::vec3 get_pos();
  float  get_vel();
  void set_pos(glm::vec3 new_pos);
  glm::vec3 translate_camera();
  void rotate(float xoffset, float yoffset);

 private:
  glm::vec3 translate_front(float delta_time);
  glm::vec3 jump(float delta_time);
  glm::vec3 translate_back(float delta_time);
  glm::vec3 translate_right(float delta_time);
  glm::vec3 translate_left(float delta_time);
  void clock();
  void update_vectors();
};

#endif
