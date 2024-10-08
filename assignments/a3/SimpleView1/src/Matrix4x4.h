//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_MATRIX4X4_H
#define A3_MATRIX4X4_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Matrix4x4 : glm::mat4x4 {
public:
    Matrix4x4 transpose();
    Matrix4x4 normalize();
    Matrix4x4 rotate(float rx, float ry, float rz, float angle);
};


#endif //A3_MATRIX4X4_H
