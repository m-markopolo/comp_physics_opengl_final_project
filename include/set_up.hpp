#ifndef SET_UP_HPP
#define SET_UP_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "definitions.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "shader.hpp"


struct MVP {
glm::mat4 M ;
glm::mat4 V ;
glm::mat4 P ;

  MVP(glm::mat4 const & m ,glm::mat4 const & v ,glm::mat4 const & p ) ;
};


struct external_filenames{
  std::string ent = "" ;
  std::string vert = "" ;
  std::string frag = "" ;
  std::string geo = "" ;
};

class Entity {

protected:
  Shader  m_shader ; 
  glm::mat4 m_projection ; 
  glm::mat4 m_model ; 

public:
  Model  m_mesh_model ; 
  Entity(std::string const& entity_fname,
                     std::string const& vert_shader_fname,
                     std::string const& frag_shader_fname);
  Entity(external_filenames) ; 
        
  virtual ~Entity(){} ; 
       
                                 // std::pair<int, int> win_dimensions);


  template<typename unif_property>
  void set_properties(std::vector<std::pair<std::string, unif_property>> const &) ;
  void set_mvp(MVP const & mvp ) ; 
  void set_mvp_skybox(glm::mat4 view_matrix ) ; 
  void set_mvp(glm::mat4 const& view_matrix,
                                 glm::vec3 const& position);
void set_mvp_and_set_scale(glm::mat4 const &view_matrix, 
                              glm::vec3 const &position, float level_scale);
  glm::mat4 get_model() const ; 
  void draw() ; 
  void drawCubemap() ; 
  void use();

  template<typename transformation>
  void transform_in_world(transformation F) ; 

};

template<typename transformation>
void Entity::transform_in_world(transformation F) {
  F(m_model) ;
}

template <typename unif_property>
void Entity::set_properties(
    std::vector<std::pair<std::string, unif_property>> const& properties) {
  struct Setter {
    Shader m_shad;
    Setter(Shader& shad) : m_shad(shad){};

    void operator()(std::pair<std::string, glm::vec2> const& vec) {
      m_shad.setVec2(vec.first, vec.second);
    }
    void operator()(std::pair<std::string, glm::vec3> const& vec) {
      m_shad.setVec3(vec.first, vec.second);
    }
    void operator()(std::pair<std::string, glm::vec4> const& vec) {
      m_shad.setVec4(vec.first, vec.second);
    }
    void operator()(std::pair<std::string, glm::mat2> const& mat) {
      m_shad.setMat2(mat.first, mat.second);
    }
    void operator()(std::pair<std::string, glm::mat3> const& mat) {
      m_shad.setMat3(mat.first, mat.second);
    }
    void operator()(std::pair<std::string, glm::mat4> const& mat) {
      m_shad.setMat4(mat.first, mat.second);
    }
  };

  Setter set_up(m_shader);
  std::for_each(properties.begin(), properties.end(),
                [&set_up](auto const & property) { set_up(property); });
}


class TheSkybox{

private: 
  GLuint load_skybox_paths(std::vector<std::string> const& face_paths) ;
public:
  void set_view(glm::mat4 const & view);
  void activate_skybox(std::vector<std::string> const & skybox_tex_fnames ) ;
  TheSkybox(std::string const & path,
            std::string const & v_shad,
            std::string const & f_shad
            ) ; 
  void draw_skybox() ; 
  void use() ; 
  void bind(GLenum TextureUnit ) ; 
private:
  Entity m_cubemap ; 
  GLuint m_textures ; 
};


class Physical_Entity ;
class Camera;

void draw_player(Entity * ent, Camera & cam,  float time );
void draw_entity(Entity * ent,  glm::mat4 view_mat, glm::vec3 pos, float time, float scale = LEVEL_SCALE);
void draw_skybox(TheSkybox * ent, glm::mat4 view_mat);

#endif
