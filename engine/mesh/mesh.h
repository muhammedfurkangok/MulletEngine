// engine/mesh/mesh.h
#pragma once

#include <vector>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include "../shader/shader.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    ~Mesh();

    Mesh(const Mesh &) = delete;

    Mesh &operator=(const Mesh &) = delete;

    Mesh(Mesh &&) = delete;

    Mesh &operator=(Mesh &&) = delete;

    void draw(const Shader &shader) const;

private:
    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    std::vector<Texture> textures_;
    unsigned int VAO = 0, VBO = 0, EBO = 0;

    void setupMesh();

    void setupPrimitiveMesh();
};