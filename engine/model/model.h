// engine/model/model.h
#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../shader/shader.h"
#include "../mesh/mesh.h"

class Model
{
public:
    explicit Model(const std::string& path);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&&) = delete;

    void draw(const Shader& shader) const;



private:
    std::vector<Texture> textures_loaded_;
    std::vector<Mesh> meshes_;
    std::string directory_;
    bool gammaCorrection_ = false;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};