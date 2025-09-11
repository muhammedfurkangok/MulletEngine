#pragma  once

#include <string>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader();

    ~Shader();

    Shader(const Shader &) = delete;

    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&) = delete;

    Shader &operator=(Shader &&) = delete;

    void init(const std::string &vertexCode, const std::string &fragmentCode);

    void use() const;

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    void checkCompileErr(GLuint shader, const std::string &type);

    void checkLinkingErr() const;

    void compile();

    void link();

    GLuint id = 0;
    GLuint vertexId_ = 0, fragmentId_ = 0;
    std::string vertexCode_, fragmentCode_;
};

