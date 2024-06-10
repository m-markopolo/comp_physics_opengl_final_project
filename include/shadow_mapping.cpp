#include "shadow_mapping.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <algorithm>

namespace{
void operator<<(std::ostream & cout_like, glm::mat4 const & mat ){

for(int i = 0 ; i < 4 ; ++i ){
  for(int j = 0 ; j < 4 ; ++j ){

    float x = mat[i][j]  ;
    cout_like << x << ",";
    }
    cout_like << '\n' ;
  }
    cout_like << '\n' ;
    cout_like << '\n' ;
}
}

glm::mat4 
create_transformation_to_directional_light_source_as_camera
(glm::vec3 light_source_position, 
  float near_plane = 1.0f, float far_plane = 7.5f, 
  float box_side = 10.0f  ){

  glm::mat4 light_space_projection = glm::ortho(-box_side, box_side, -box_side, box_side, near_plane, far_plane) ;
  glm::mat4 light_space_view = glm::lookAt(light_source_position, {0.0,0.0,0.0}, {0.0,1.0,0.0});


 return light_space_projection * light_space_view ; 
}


unsigned gen_texture_for_use_as_depth_buffer(){
  unsigned constexpr SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024 ;  

  unsigned depthMap ; 
  glGenTextures(1, &depthMap) ;
  glBindTexture(GL_TEXTURE_2D, depthMap) ; 

  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
               SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL ) ;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


  return depthMap ; 
}

ShadowCastingEntity::ShadowCastingEntity(std::string const& entity_fname,
                     std::string const& vert_shader_fname,
                     std::string const& frag_shader_fname,
                                 std::pair<int, int> win_dimensions):
  // m_mesh_model(entity_fname),m_shader(vert_shader_fname, frag_shader_fname),
  Entity(entity_fname,vert_shader_fname,frag_shader_fname, win_dimensions),
  m_shadow_mapping_shader("shaders/fragment/shadow_map_fr.glsl", "shaders/vertex/shadow_map_ve.glsl")
  ,m_depthMapFBO(gen_texture_for_use_as_depth_buffer()),
m_win_dimensions(win_dimensions)
{
    
} 

unsigned ShadowCastingEntity::attach_depth_buffer_in_framebuffer_and_draw(){

  unsigned depthMap = gen_texture_for_use_as_depth_buffer() ; 
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

  std::for_each(m_mesh_model.meshes.begin(), m_mesh_model.meshes.end(),[&](Mesh &  mesh){
    mesh.Draw(m_shadow_mapping_shader) ;
  });
  return depthMap; 
}


void ShadowCastingEntity::gen_shadow_map(glm::vec3 const& light_source_pos ){
  unsigned constexpr SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024 ;  
  glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
  m_shadow_mapping_shader.use() ; 
  m_shadow_mapping_shader.setMat4("ls_trans", create_transformation_to_directional_light_source_as_camera(light_source_pos) ) ; 
  m_shadow_mapping_shader.setMat4("model", glm::mat4(1.0f)) ;
  glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  m_depthMap = attach_depth_buffer_in_framebuffer_and_draw() ; 
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, m_win_dimensions.first, m_win_dimensions.second);
}

