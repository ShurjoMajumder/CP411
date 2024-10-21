//
// Created by shurj on 15-Oct-2024.
//

#ifndef A3_CAMERA_H
#define A3_CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

typedef enum {
    CAMERA_PERSPECTIVE = 0,
    CAMERA_ORTHOGRAPHIC
} CameraProjection;

class Camera {
    Camera() = default;

    glm::vec3 GetForward();
    glm::vec3 GetUp();
    glm::vec3 GetRight();

    /**
     * Rotates the camera about its 'up' vector. Yaw means looking 'left' or 'right'.
     *
     * @param angle The angle to turn in radians.
     * @param rotateAroundTarget Circles the camera around its target if true, else rotates around its position.
     */
    void Yaw(float angle, bool rotateAroundTarget);

    /**
     * Rotates the camera about its 'right' vector. Pitch means looking 'up' or 'down'.
     *
     * @param angle The angle to turn in radians.
     * @param lockView Prevents the camera from over-rotating (somersaults).
     * @param rotateAroundTarget Circles the camera around its target if true, else rotates around its position.
     */
    void Pitch(float angle, bool rotateAroundTarget);

    /**
     * Rotates the camera around its forward vector. Roll means rolling side-to-side.
     *
     * @param angle Anle to turn in radians.
     */
    void Roll(float angle);

    glm::mat4x4 GetViewMatrix();
    glm::mat4x4 GetProjectionMatrix(float aspectRatio);

private:
    glm::vec3 m_position{};
    glm::vec3 m_target{};
    glm::vec3 m_up{};
    float m_fovY{};
    float m_nearPlane{};
    float m_farPlane{};
    CameraProjection m_projectionType{};

    Camera(glm::vec3 position, glm::vec3 target, float fovY, CameraProjection projection);
};

#endif //A3_CAMERA_H
