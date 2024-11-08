//
// Created by shurj on 07-Nov-2024.
//

#ifndef A4_AXES_H
#define A4_AXES_H

#include <memory>

#include <Graphics/Graphics.h>

class Axes {
public:
    static std::shared_ptr<Graphics::CanvasItem> Create();
};

#endif //A4_AXES_H
