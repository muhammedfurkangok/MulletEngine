#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// Hareket tipleri
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Varsayılan değerler
const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw = YAW, float pitch = PITCH);
    ~Camera();

    // Özellikler
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    glm::mat4 projection;

    // Euler açılar
    float yaw;
    float pitch;

    // Ayarlar
    float movementSpeed;
    float mouseSensitivity;

    // Fonksiyonlar
    glm::mat4 getViewMatrix();
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    void updateCameraVectors();
};
