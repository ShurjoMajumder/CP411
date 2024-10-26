//
// Created by shurj on 25-Oct-2024.
//

#ifndef A3_HOUSE_H
#define A3_HOUSE_H

#include <memory>
#include "Shape.h"

class House {
public:
    static std::shared_ptr<Shape> Create();
};


#endif //A3_HOUSE_H
