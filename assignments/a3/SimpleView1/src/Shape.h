//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_SHAPE_H
#define A3_SHAPE_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "ObjectMesh.h"

class Shape {
private:
    glm::mat4x4 m_MC;
    Mesh m_mesh;
};


#endif //A3_SHAPE_H
