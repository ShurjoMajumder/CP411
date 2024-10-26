//
// Created by shurj on 25-Oct-2024.
//

#ifndef A3_CUBE_H
#define A3_CUBE_H


#include <memory>

#include "Shape.h"

class Cube {
public:
    static std::shared_ptr<Shape> Create();
};

#endif //A3_CUBE_H
