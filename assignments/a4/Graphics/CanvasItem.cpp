//
// Created by shurj on 05-Nov-2024.
//

#include "CanvasItem.h"

using namespace Graphics;

const std::shared_ptr<ShaderProgram>& CanvasItem::GetShaderProgram() const {
    return m_program;
}

void CanvasItem::Draw() const {
    m_program->Use();
    m_mesh->Draw();
}

void CanvasItem::Reset() {
    m_position = {0, 0, 0};
    m_scale = {1, 1, 1};
    m_rotation = {0, 0, 0};
}

CanvasItem::CanvasItem(const std::shared_ptr<Mesh<CanvasItemVertex>> &mesh, const std::shared_ptr<ShaderProgram> &program) {
    m_mesh = mesh;
    m_program = program;
    m_position = {0, 0, 0};
    m_scale = {1, 1, 1};
    m_rotation = {0, 0, 0};
}

void CanvasItem::Translate(glm::vec3 xyz) {
    m_position += xyz;
}

void CanvasItem::Rotate(float rx, float ry, float rz) {
    m_rotation.x += rx;
    m_rotation.y += ry;
    m_rotation.z += rz;
}

void CanvasItem::RotateOrigin(glm::vec3 rxryrz, glm::vec3 origin) {
    Rotate(rxryrz.x, rxryrz.y, rxryrz.z);

    glm::vec3 relativePosition = m_position - origin;
    glm::vec3 rotatedPosition = glm::rotate(relativePosition, rxryrz.x, {1, 0, 0});
    rotatedPosition = glm::rotate(rotatedPosition, rxryrz.y, {0, 1, 0});
    rotatedPosition = glm::rotate(rotatedPosition, rxryrz.z, {0, 0, 1});
    glm::vec3 travel = rotatedPosition - relativePosition;
    m_position += travel;
}

void CanvasItem::Scale(float scale) {
    m_scale *= scale;
}

glm::mat4x4 CanvasItem::GetTransformationMatrix() const {
    glm::mat4x4 transform = glm::identity<glm::mat4x4>();

    transform = glm::scale(transform, m_scale);

    transform = glm::translate(transform, m_position);

    transform = glm::rotate(transform, m_rotation.x, {1, 0, 0});
    transform = glm::rotate(transform, m_rotation.y, {0, 1, 0});
    transform = glm::rotate(transform, m_rotation.z, {0, 0, 1});

//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            std::cout << transform[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }

    return transform;
}

CanvasItem::~CanvasItem() = default;
