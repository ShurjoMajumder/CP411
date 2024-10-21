//
// Created by shurj on 15-Oct-2024.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, float fovY, CameraProjection projection) {
    m_position = position;
    m_target = target;
    m_fovY = fovY;
    m_projectionType = projection;

    m_up = glm::vec3(0, 0, 0);
}

glm::vec3 Camera::GetForward() {
    return glm::normalize(m_target - m_position);
}

glm::vec3 Camera::GetUp() {
    return glm::normalize(m_up);
}

void Camera::Yaw(float angle, bool rotateAroundTarget) {
    glm::vec3 up = GetUp();

    // Get the direction the camera is looking.
    glm::vec3 lookDirection = m_target - m_position;

    // Update direction camera is looking.
    lookDirection = glm::rotate(lookDirection, angle, up);

    if (rotateAroundTarget) {
        // Rotate position about the target.
        m_position = m_target - lookDirection;
    } else {
        // Remain stationary and "look" in a different direction.
        m_target = m_position + lookDirection;
    }
}

void Camera::Pitch(float angle, bool rotateAroundTarget) {
    glm::vec3 up = GetUp();
    glm::vec3 right = GetRight();

    // Get the direction the camera is looking.
    glm::vec3 lookDirection = m_target - m_position;

    // Update direction camera is looking.
    lookDirection = glm::rotate(lookDirection, angle, right);

    // Update up direction.
    m_up = glm::rotate(m_up, angle, right);

    if (rotateAroundTarget) {
        // Rotate position about the target.
        m_position = m_target - lookDirection;
    } else {
        // Remain stationary and "look" in a different direction.
        m_target = m_position + lookDirection;
    }
}

void Camera::Roll(float angle) {
    // Get axis of rotation.
    glm::vec3 forwards = GetForward();

    // Update up direction.
    m_up = glm::rotate(m_up, angle, forwards);
}

glm::vec3 Camera::GetRight() {
    glm::vec3 forward = GetForward();
    glm::vec3 up = GetUp();

    glm::vec3 forwardCrossUp = glm::cross(forward, up);

    return glm::normalize(forwardCrossUp);
}

glm::mat4x4 Camera::GetViewMatrix() {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4x4 Camera::GetProjectionMatrix(float aspectRatio) {
    if (m_projectionType == CAMERA_PERSPECTIVE) {
        return glm::perspective(m_fovY, aspectRatio, m_nearPlane, m_farPlane);
    }
    else if (m_projectionType == CAMERA_ORTHOGRAPHIC) {
        float top = m_fovY / 2.f;
        float right = top * aspectRatio;

        return glm::ortho(-right, right, -top, top, m_nearPlane, m_farPlane);
    }

    return {1.f};
}

