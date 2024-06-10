#include "controls.hpp"

#include <glad/glad.h>
// #include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

Camera::Camera(GLFWwindow *win, glm::vec3 init_pos, glm::vec3 init_world_up,
               float init_yaw, float init_pitch, float init_vel,
               float init_mouse_sensitivity) {
  m_win = win ;
  pos = init_pos;
  world_up = init_world_up;
  yaw = init_yaw;
  pitch = init_pitch;
  vel = init_vel;
  mouse_sensitivity = init_mouse_sensitivity;

  update_vectors();
}
glm::vec3 Camera::translate_camera() {

  clock();

  if (glfwGetKey(m_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_win, true);

  if (glfwGetKey(m_win, GLFW_KEY_SPACE) == GLFW_PRESS)
    return this->jump(delta_time);
  if (glfwGetKey(m_win, GLFW_KEY_W) == GLFW_PRESS)
    return this->translate_front(delta_time);
  if (glfwGetKey(m_win, GLFW_KEY_S) == GLFW_PRESS)
    return this->translate_back(delta_time);
  if (glfwGetKey(m_win, GLFW_KEY_D) == GLFW_PRESS)
    return this->translate_right(delta_time);
  if (glfwGetKey(m_win, GLFW_KEY_A) == GLFW_PRESS)
    return this->translate_left(delta_time);

  return {} ;
}

void Camera::rotate(float xoffset, float yoffset) {
  if (pitch > 88.9f)
    pitch = 88.9f;
  else if (pitch <= -88.9f)
    pitch = -88.9f;

  if (std::abs(yaw) > 360.0f) yaw = 0.0f;

  yaw -= xoffset * mouse_sensitivity;
  pitch -= yoffset * mouse_sensitivity;

  update_vectors();
}

glm::mat4 Camera::get_view_matrix() {
  return glm::lookAt(pos, pos + front, up);
}

glm::vec3 Camera::get_pos() {
  return pos ; 
}
float Camera::get_vel() {
  return vel ; 
}
void Camera::set_pos(glm::vec3 new_pos) {
  pos = std::move(new_pos) ;
}
glm::vec3 Camera::jump(float delta_time) {
  auto diff = vel * delta_time * glm::vec3{0,0,1};
  pos += diff ;
return diff ;
}

glm::vec3 Camera::translate_front(float delta_time) {
  auto diff = vel * delta_time * front;
  pos += diff ; 
return diff ;
}

glm::vec3 Camera::translate_back(float delta_time) {
  auto diff = vel * delta_time * front;
  pos -= diff ; 
return -diff ;
}

glm::vec3 Camera::translate_right(float delta_time) {
  auto diff = vel * delta_time * right;
  pos += diff ;  
return diff ;
}

glm::vec3 Camera::translate_left(float delta_time) {
  auto diff = vel * delta_time * right;
  pos -= diff ;
return -diff ;
}

void Camera::clock() {
  t2 = glfwGetTime();  // elased time [sec] since glfwInit()
  delta_time = t2 - t1;
  t1 = t2;
}

void Camera::update_vectors() {
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  front.z = sin(glm::radians(pitch));
  front = glm::normalize(front);
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}

