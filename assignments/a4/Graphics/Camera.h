//
// Created by shurj on 15-Oct-2024.
//

#ifndef A3_CAMERA_H
#define A3_CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

namespace Graphics {
    typedef enum {
        CAMERA_PERSPECTIVE = 0,
        CAMERA_ORTHOGRAPHIC
    } CameraProjection;

    class Camera {
    public:
        /**
         * Creates a standard z-up camera (to be compatible with 3D modelling software and mathematics).
         *
         * @param fovY Field of view.
         * @param nearPlane Near clip plane.
         * @param farPlane Far clip plane.
         * @param projection Projection type (Perspective or Orthographic).
         */
        Camera(float fovY, float nearPlane, float farPlane, CameraProjection projection);

        /**
         * Creates a standard z-up camera with default settings.
         */
        Camera();

        glm::vec3 GetForward() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;

        /**
         * Moves the camera along its own relative co-ordinates.
         * @param directionAndDistance A vector with information about how to move. X = lateral motion, Y = forwards/backwards, Z = up/down.
         */
        void Move(glm::vec3 directionAndDistance);

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
         * @param rotateAroundTarget Circles the camera around its target if true, else rotates around its position.
         */
        void Pitch(float angle, bool rotateAroundTarget);

        /**
         * Rotates the camera around its forward vector. Roll means rolling side-to-side.
         *
         * @param angle Angle to turn in radians.
         */
        void Roll(float angle);

        /**
         * Generates and returns the view matrix described by the camera.
         *
         * @return
         */
        glm::mat4x4 GetViewMatrix() const;

        /**
         * Generates and returns the projection matrix described by the camera.
         *
         * @param aspectRatio Viewport aspect ratio.
         * @return
         */
        glm::mat4x4 GetProjectionMatrix(float aspectRatio) const;

        void Reset();

        float NearPlane{};
        float FarPlane{};
    private:
        glm::vec3 m_position{};
        glm::vec3 m_target{};
        glm::vec3 m_up{};
        float m_fovY{};

        CameraProjection m_projectionType{};
    };
}



#endif //A3_CAMERA_H
