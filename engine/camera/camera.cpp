#include "camera.h"

// Constructor with vectors
Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, float _yaw, float _pitch)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)),
          movementSpeed(SPEED),
          mouseSensitivity(SENSITIVITY)
{
    position = _position;
    worldUp  = _worldUp;
    yaw      = _yaw;
    pitch    = _pitch;
    updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)  position += front * velocity;
    if (direction == BACKWARD) position -= front * velocity;
    if (direction == LEFT)     position -= right * velocity;
    if (direction == RIGHT)    position += right * velocity;

    // debug
    // std::cout << "Camera.position: " << glm::to_string(position) << std::endl;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    // yeni front
    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(_front);

    // right & up
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}
