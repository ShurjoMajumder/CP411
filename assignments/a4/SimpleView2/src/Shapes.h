//
// Created by shurj on 07-Nov-2024.
//

#ifndef A4_SHAPES_H
#define A4_SHAPES_H

#include <Graphics/Graphics.h>

#include "Cube.h"
#include "Pyramid.h"
#include "House.h"
#include "Axes.h"

namespace Shapes {
    void GenShapes(const std::shared_ptr<Graphics::World>&);
}

#endif //A4_SHAPES_H
