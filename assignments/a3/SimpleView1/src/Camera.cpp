//
// Created by shurj on 15-Oct-2024.
//

#include "Camera.h"

/**
 * Creates a standard z-up camera (to be compatible with 3D modelling software and mathematics).
 *
 * @param fovY Field of view.
 * @param nearPlane Near clip plane.
 * @param farPlane Far clip plane.
 * @param projection Projection type (Perspective or Orthographic).
 */
Camera::Camera(float fovY, float nearPlane, float farPlane,
               CameraProjection projection) {
    m_projectionType = projection;
    m_fovY = fovY;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;

    if (m_projectionType == CAMERA_PERSPECTIVE) {
        m_position = {0, 0, 0};
        m_target   = {0, 1, 0};
        m_up       = {0, 0, 1};
    } else if (m_projectionType == CAMERA_ORTHOGRAPHIC) {
        m_position = {0, 0, 0};
        m_target   = {0, 0, 1};
        m_up       = {0, 1, 0};
    }
}

/**
 * Creates a standard z-up camera with default settings.
 */
Camera::Camera() {
    m_projectionType = CAMERA_PERSPECTIVE;
    m_fovY = 90;
    m_nearPlane = 0;
    m_farPlane = 100;
    m_position = {0, 0, 0};
    m_target = {0, 1, 0};
    m_up = {0, 0, 1};
}

glm::vec3 Camera::GetForward() {
    return glm::normalize(m_target - m_position);
}

glm::vec3 Camera::GetUp() {
    return glm::normalize(m_up);
}

glm::vec3 Camera::GetRight() {
    glm::vec3 forward = GetForward();
    glm::vec3 up = GetUp();

    glm::vec3 forwardCrossUp = glm::cross(forward, up);

    return glm::normalize(forwardCrossUp);
}

/**
 * Moves the camera along its own relative co-ordinates.
 * @param directionAndDistance A vector with information about how to move. X = lateral motion, Y = forwards/backwards, Z = up/down.
 */
void Camera::Move(glm::vec3 directionAndDistance) {
    glm::vec3 forward = GetForward();
    glm::vec3 up = GetUp();
    glm::vec3 right = GetRight();

    glm::vec3 leftAndRight = directionAndDistance.x * right;
    glm::vec3 forwardsAndBackwards = directionAndDistance.y * forward;
    glm::vec3 upAndDown = directionAndDistance.z * up;
    glm::vec3 totalMovement = leftAndRight + forwardsAndBackwards + upAndDown;

    m_position += totalMovement;
    m_target += totalMovement;
}

/**
 * Rotates the camera about its 'up' vector. Yaw means looking 'left' or 'right'.
 *
 * @param angle The angle to turn in radians.
 * @param rotateAroundTarget Circles the camera around its target if true, else rotates around its position.
 */
void Camera::Yaw(float angle, bool rotateAroundTarget) {
    glm::vec3 up = GetUp();

    // Get the direction the camera is looking.
    glm::vec3 lookDirection = m_target - m_position;

    // Update direction camera is looking.
    lookDirection = glm::rotate(lookDirection, angle, up);

    if (rotateAroundTarget) {
        // Rotate position about the target.
        m_position = m_target - lookDirection;
        return;
    }

    // Remain stationary and "look" in a different direction.
    m_target = m_position + lookDirection;
}

/**
 * Rotates the camera about its 'right' vector. Pitch means looking 'up' or 'down'.
 *
 * @param angle The angle to turn in radians.
 * @param rotateAroundTarget Circles the camera around its target if true, else rotates around its position.
 */
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

/**
 * Rotates the camera around its forward vector. Roll means rolling side-to-side.
 *
 * @param angle Angle to turn in radians.
 */
void Camera::Roll(float angle) {
    // Get axis of rotation.
    glm::vec3 forwards = GetForward();

    // Update up direction.
    m_up = glm::rotate(m_up, angle, forwards);
}

/**
 * Generates and returns the view matrix described by the camera.
 *
 * @return
 */
glm::mat4x4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_target, m_up);
}

/**
 * Generates and returns the projection matrix described by the camera.
 *
 * @param aspectRatio Viewport aspect ratio.
 * @return
 */
glm::mat4x4 Camera::GetProjectionMatrix(float aspectRatio) const {
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

void Camera::Reset() {

}
