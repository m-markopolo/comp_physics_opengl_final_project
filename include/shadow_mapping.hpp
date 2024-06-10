#ifndef SHADOW_MAPPING_HPP 
#define SHADOW_MAPPING_HPP 

#include "shader.hpp"
#include "set_up.hpp"

class ShadowCastingEntity : public Entity{

private : 
  Shader m_shadow_mapping_shader ;
  GLuint m_depthMapFBO ; 
  GLuint m_depthMap ; 
  std::pair<int,int> m_win_dimensions ; 
                               
public:
  ShadowCastingEntity(std::string const& entity_fname,
                     std::string const& vert_shader_fname,
                     std::string const& frag_shader_fname,
                                 std::pair<int, int> win_dimensions);
                                

  void gen_shadow_map(glm::vec3 const& light_source_pos );

private : 
  unsigned map_shadows(glm::vec3 const& light_source_pos );
  unsigned attach_depth_buffer_in_framebuffer_and_draw();


};




#endif
