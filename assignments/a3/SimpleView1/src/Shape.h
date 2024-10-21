//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_SHAPE_H
#define A3_SHAPE_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "ObjectMesh.h"

struct ShapeVertex {
    glm::vec3 Position;
    glm::vec4 Color;
};

class Shape {
    static std::shared_ptr<Shape> CubeFactory();
    static std::shared_ptr<Shape> PyramidFactory();
    static std::shared_ptr<Shape> HouseFactory();
private:
    glm::mat4x4 m_MC;
    ObjectMesh<ShapeVertex> m_objectMesh;
};

#endif //A3_SHAPE_H
