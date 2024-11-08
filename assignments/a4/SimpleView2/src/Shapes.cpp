//
// Created by shurj on 07-Nov-2024.
//

#include "Shapes.h"

void Shapes::GenShapes(const std::shared_ptr<Graphics::World>& world) {
    auto cube = Cube::Create();
    auto pyramid = Pyramid::Create();
    auto house = House::Create();

    pyramid->Translate({-1.5, 0, 0});

    house->Translate({-3, 0, 0});

    world->AddCanvasItem(cube);
    world->AddCanvasItem(pyramid);
    world->AddCanvasItem(house);
}
