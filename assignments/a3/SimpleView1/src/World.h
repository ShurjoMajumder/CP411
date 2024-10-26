//
// Created by shurj on 15-Oct-2024.
//

#ifndef A3_WORLD_H
#define A3_WORLD_H

#include <string>
#include <memory>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Shape.h"
#include "Camera.h"

class World {
public:
    World(int screenWidth, int screenHeight);

    int GetWindowWidth() const;
    int GetWindowHeight() const;

    void Draw() const;

    std::shared_ptr<Shape> SearchById(int i);
    Camera& GetCamera();

    void Reset();

private:
    int m_screenWidth, m_screenHeight;
    std::vector<std::shared_ptr<Shape>> m_shapes;
    Camera m_camera;
};

#endif //A3_WORLD_H
