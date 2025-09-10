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

};