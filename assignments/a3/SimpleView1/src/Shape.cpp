//
// Created by shurj on 08-Oct-2024.
//

#include "Shape.h"


Shape::Shape(const std::shared_ptr<ObjectMesh<ShapeVertex>> &mesh, const std::shared_ptr<ShaderProgram> &program) {
    m_objectMesh = mesh;
    m_shaderProgram = program;
    m_position = {0, 0, 0};
    m_scale = {1, 1, 1};
    m_rotation = {0, 0, 1};
}

Shape::Shape(Shape &&shape) noexcept {
    m_objectMesh = std::move(shape.m_objectMesh);
}

Shape::~Shape() = default;

void Shape::Draw() {
    m_shaderProgram->Use();
    m_shaderProgram->SetUniform("M", GetTransformationMatrix());
    m_objectMesh->Draw();
}

const std::shared_ptr<ShaderProgram> &Shape::GetShaderProgram() const {
    return m_shaderProgram;
}

void Shape::Reset() {
    m_position = {0, 0, 0};
    m_scale = {1, 1, 1};
    m_rotation = {0, 0, 1};
}

void Shape::Translate(glm::vec3 xyz) {
    m_position += xyz;
}

void Shape::Rotate(float rx, float ry, float rz) {
    m_rotation.x += rx;
    m_rotation.y += ry;
    m_rotation.z += rz;
}

void Shape::RotateOrigin(glm::vec3 rxryrz, glm::vec3 origin) {
    // Just trust me bro.
    Translate(-origin);
    Rotate(rxryrz.x, rxryrz.y, rxryrz.z);
    Translate(origin);
}

void Shape::Scale(float scale) {
    m_scale *= scale;
}

glm::mat4x4 Shape::GetTransformationMatrix() {
    glm::mat4x4 rotation = glm::identity<glm::mat4x4>();
    rotation = glm::rotate(rotation, m_rotation.x, {1, 0, 0});
    rotation = glm::rotate(rotation, m_rotation.y, {0, 1, 0});
    rotation = glm::rotate(rotation, m_rotation.z, {0, 0, 1});

    glm::mat4x4 translation = glm::translate(glm::identity<glm::mat4x4>(), m_position);
    glm::mat4x4 scale = glm::scale(glm::identity<glm::mat4x4>(), m_scale);

    glm::mat4x4 transform = rotation * translation * scale;

    return transform;
}
