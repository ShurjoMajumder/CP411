//
// Created by shurj on 15-Oct-2024.
//

#include "World.h"

using namespace Graphics;

World::World() = default;

World::World(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    m_camera = Camera(glm::pi<float>() / 2, 0.1, 100, CAMERA_PERSPECTIVE);
}

World::~World() {
    std::cout << "World successfully destroyed! Mua-ha-ha!" << std::endl;
}

World::World(const World &other) {
    m_screenWidth = other.m_screenWidth;
    m_screenWidth = other.m_screenHeight;
    m_canvasItems = other.m_canvasItems;
    m_camera = other.m_camera;
}

World::World(World &&other) noexcept {
    m_screenWidth = other.m_screenWidth;
    m_screenHeight = other.m_screenHeight;
    m_camera = other.m_camera;
    m_canvasItems = std::move(other.m_canvasItems);
}

World &World::operator=(const World &other) noexcept {
    m_screenWidth = other.m_screenWidth;
    m_screenWidth = other.m_screenHeight;
    m_canvasItems = other.m_canvasItems;
    m_camera = other.m_camera;

    return *this;
}

World &World::operator=(World &&other) noexcept {
    m_screenWidth = other.m_screenWidth;
    m_screenHeight = other.m_screenHeight;
    m_camera = other.m_camera;
    m_canvasItems = std::move(other.m_canvasItems);

    return *this;
}

int World::GetWindowWidth() const {
    return m_screenWidth;
}

int World::GetWindowHeight() const {
    return m_screenHeight;
}

void World::ResizeWindow(int width, int height) {
    m_screenWidth = width;
    m_screenHeight = height;
}

void World::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspectRatio = (float)m_screenWidth / (float)m_screenHeight;

    glm::mat4x4 view = m_camera.GetViewMatrix();
    glm::mat4x4 projection = m_camera.GetProjectionMatrix(aspectRatio);
    glm::mat4x4 VP = projection * view;

    for (const auto &canvasItem : m_canvasItems) {
        glm::mat4x4 MVP = VP * canvasItem->GetTransformationMatrix();
        canvasItem->GetShaderProgram()->SetUniform("MVP", MVP);
        canvasItem->Draw();  // the canvasItem object applies the model transform itself.
    }

    glutSwapBuffers();
}

void World::AddCanvasItem(const std::shared_ptr<CanvasItem>& canvasItem) {
    m_canvasItems.push_back(canvasItem);
}

std::shared_ptr<CanvasItem> World::SearchById(int i) {
    return m_canvasItems.at(i);
}

void World::Reset() {
    m_camera.Reset();
    m_canvasItems = {};
}

Camera &World::GetCamera() {
    return m_camera;
}
