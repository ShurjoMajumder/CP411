//
// Created by shurj on 08-Oct-2024.
//

#include "Shape.h"

std::shared_ptr<Shape> Shape::CubeFactory() {
    return std::shared_ptr<Shape>();
}

std::shared_ptr<Shape> Shape::PyramidFactory() {
    return CubeFactory();
}

std::shared_ptr<Shape> Shape::HouseFactory() {
    return CubeFactory();
}
