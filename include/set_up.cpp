#include "set_up.hpp"

#include <algorithm>
#include <glm/fwd.hpp>

#include "controls.hpp"
#include "physical.hpp"
#include "stb_image.h"

#include "definitions.hpp"

Entity::Entity(std::string const& entity_fname,
               std::string const& vert_shader_fname,
               std::string const& frag_shader_fname)
               // std::pair<int, int> win_dimensions)
    : m_mesh_model(entity_fname),
      m_shader(vert_shader_fname, frag_shader_fname) {
m_projection = glm::perspective(glm::radians(90.0f),
                                static_cast<float>(SCR_WIDTH) /
                                    static_cast<float>(SCR_HEIGHT),
                                0.05f, 1000.0f);
}

Entity::Entity(external_filenames f_names) : Entity(f_names.ent, f_names.vert, f_names.frag){}

void Entity::set_mvp(MVP const &mvp) {
  set_properties(

      std::vector<std::pair<std::string, glm::mat4>>{
          {"model", mvp.M}, {"view", mvp.V}, {"projection", mvp.P}});
}

void Entity::set_mvp(glm::mat4 const &view_matrix, glm::vec3 const &position){

  using namespace glm ; 
  m_model = mat4(1.0f);
  m_model =
      scale(m_model, vec3(LEVEL_SCALE, LEVEL_SCALE, LEVEL_SCALE));
  m_model = translate(m_model, position);

  set_properties(std::vector<std::pair<std::string, mat4>>{
      {"mvp", m_projection * view_matrix * m_model},
      {"model", m_model},
      {"view", view_matrix},
      {"projection", m_projection}});
}

void Entity::set_mvp_and_set_scale(glm::mat4 const &view_matrix, glm::vec3 const &position, float level_scale){

  using namespace glm ; 
  m_model = mat4(1.0f);
  m_model =
      scale(m_model, vec3(level_scale, level_scale, level_scale));
  m_model = translate(m_model, position);

  set_properties(std::vector<std::pair<std::string, mat4>>{
      {"mvp", m_projection * view_matrix * m_model},
      {"model", m_model},
      {"view", view_matrix},
      {"projection", m_projection}});
}

void Entity::draw() { m_mesh_model.Draw(m_shader); }
void Entity::drawCubemap() { m_mesh_model.drawCubemap(); }
void Entity::use() { m_shader.use(); }

glm::mat4 Entity::get_model() const { return m_model ;}

MVP::MVP(glm::mat4 const &m, glm::mat4 const &v, glm::mat4 const &p)
    : M(m), V(v), P(p) {}

void Entity::set_mvp_skybox(glm::mat4 view_matrix) {
  using namespace glm;
  view_matrix = mat4(mat3(view_matrix));
  set_properties(std::vector<std::pair<std::string, glm::mat4>>{
      {"view", view_matrix}, {"projection", m_projection}});
}

std::vector<std::string> gen_paths(std::string const & path){
  return {
    path + "/" + "right.png",
    path + "/" + "left.png",
    path + "/" + "top.png",
    path + "/" + "bottom.png",
    path + "/" + "front.png",
    path + "/" + "back.png"
  } ;
}
TheSkybox::TheSkybox(std::string const &path,
                     std::string const &v_shad,
                     std::string const &f_shad)
    : m_textures(load_skybox_paths(gen_paths(path)))
      , m_cubemap ("obj/cubemap.obj", v_shad, f_shad)
   {}

void load_cubemap_side(std::string const &path, int axis) {

  int width, height, nrChannels;
                  unsigned char* data =
                      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
                  if (data) {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + axis , 
                                 0,
                                 GL_RGB,
                                 width,
                                 height,
                                 0,
                                 GL_RGB,
                                 GL_UNSIGNED_BYTE,
                                 data);
                stbi_image_free(data) ;
                  
                  }else{
                  std::cerr << "Cubemap tex failed to load at path: " << path << '\n' ;
                  stbi_image_free(data) ;
                  }

}

GLuint TheSkybox::load_skybox_paths(std::vector<std::string> const& face_paths) {
  GLuint texture_ID;
  glGenTextures(1, &texture_ID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ID);

  std::for_each(face_paths.begin(), face_paths.end(),
                [&](std::string const& path) {
                load_cubemap_side(path, std::distance(face_paths.data(), &path )) ;
                });
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return texture_ID ; 
}
void TheSkybox::set_view(glm::mat4 const & view){
  m_cubemap.set_mvp_skybox(view)  ;
}

void TheSkybox::activate_skybox(std::vector<std::string> const & skybox_tex_fnames ){
  m_textures = load_skybox_paths(skybox_tex_fnames) ;
}

void TheSkybox::use(){
  m_cubemap.use() ; 
}
void TheSkybox::bind(GLenum texture_unit){
  glActiveTexture(texture_unit) ;
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures) ;
}
void TheSkybox::draw_skybox(){
  glDepthMask(GL_FALSE);
  glDisable(GL_CULL_FACE);  

  bind(GL_TEXTURE0  ) ;
  m_cubemap.drawCubemap() ; 

  glDepthMask(GL_TRUE);
  glEnable(GL_CULL_FACE);  
}

void draw_player(Entity * ent, Camera & cam,  float time){

  auto translation = cam.translate_camera();
  if( auto phy_ent = dynamic_cast<Physical_Entity*>(ent); phy_ent ){
    cam.set_pos(phy_ent->p.get_pos() );
    draw_entity(ent,  cam.get_view_matrix(), cam.get_pos() + translation, time );
  }
}
void draw_entity(Entity * ent,  glm::mat4 view_mat, glm::vec3 pos, float time, float scale ){

  ent->use();
  if( auto phy_ent = dynamic_cast<Physical_Entity*>(ent); phy_ent ){
    if(pos != glm::vec3{}) phy_ent->set_pos(pos) ;
    phy_ent->recalculate_position_and_set_mvp(std::move(view_mat), time, scale ) ;
  }else{
    ent->set_mvp_and_set_scale(view_mat, std::move(pos), scale) ;
  }
  ent->draw() ;
}

void draw_skybox(TheSkybox * ent, glm::mat4 view_mat){
    ent->use() ; 
    ent->set_view(std::move(view_mat)) ;
    ent->draw_skybox() ; 
}


