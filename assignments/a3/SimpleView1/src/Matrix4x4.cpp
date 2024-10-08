//
// Created by shurj on 08-Oct-2024.
//

#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::transpose() {
    glm::mat4x4 result = glm::transpose(*this);
    Matrix4x4 cpy = Matrix4x4{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            cpy[row][column] = result[row][column];
        }
    }
    return cpy;
}

Matrix4x4 Matrix4x4::normalize() {
    Matrix4x4 cpy = Matrix4x4{};
    float det = glm::determinant(*this);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            cpy[row][column] = (*this)[row][column] / det;
        }
    }
    return cpy;
}

Matrix4x4 Matrix4x4::rotate(float rx, float ry, float rz, float angle) {
    glm::mat4x4 result = glm::rotate(*this, angle, glm::vec3(rx, ry, rz));
    Matrix4x4 cpy = Matrix4x4{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            cpy[row][column] = result[row][column];
        }
    }
    return cpy;
}
