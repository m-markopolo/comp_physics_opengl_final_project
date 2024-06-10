#ifndef MODEL_HPP
#define MODEL_HPP

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "shader.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory,
                             bool gamma = false);

class Model {
 public:

  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;
  bool gammaCorrection;

  Model(std::string const &path_to_model, bool gamma = false );

  void Draw(Shader &shader);
  void drawCubemap() ;

 private:
  void loadModel(std::string const &path_to_model);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};

#endif
