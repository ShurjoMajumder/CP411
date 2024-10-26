//
// Created by shurj on 15-Oct-2024.
//

#include "World.h"
#include "Cube.h"
#include "Pyramid.h"
#include "House.h"


World::World(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_shapes.push_back(Cube::Create());
    m_shapes.push_back(Pyramid::Create());
    m_shapes.push_back(House::Create());

    m_camera = Camera(glm::pi<float>() / 2, 0.1, 100, CAMERA_PERSPECTIVE);
}

int World::GetWindowWidth() const {
    return m_screenWidth;
}

int World::GetWindowHeight() const {
    return m_screenHeight;
}

void World::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspectRatio = (float)m_screenWidth / (float)m_screenHeight;

    glm::mat4x4 view = m_camera.GetViewMatrix();
    glm::mat4x4 projection = m_camera.GetProjectionMatrix(aspectRatio);
    glm::mat4x4 PV = projection * view;

    for (const auto &shape : m_shapes) {
        shape->GetShaderProgram()->SetUniform("PV", PV);
        shape->Draw();  // the shape object applies the model transform itself.
    }

    glutSwapBuffers();
}

std::shared_ptr<Shape> World::SearchById(int i) {
    return m_shapes.at(i);
}

void World::Reset() {
    m_camera.Reset();
}

Camera &World::GetCamera() {
    return m_camera;
}
