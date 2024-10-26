//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_SHAPE_H
#define A3_SHAPE_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

#include "ObjectMesh.h"


struct ShapeVertex {
    glm::vec3 Position;
    glm::vec4 Color;
};

class Shape {
public:

    Shape(const std::shared_ptr<ObjectMesh<ShapeVertex>> &mesh, const std::shared_ptr<ShaderProgram> &program);
    Shape(Shape&& shape) noexcept;
    ~Shape();

    const std::shared_ptr<ShaderProgram> &GetShaderProgram() const;

    void Draw();
    void Reset();

    void Translate(glm::vec3 xyz);
    void Rotate(float rx, float ry, float rz);
    void RotateOrigin(glm::vec3 rxryrz, glm::vec3 origin);
    void Scale(float scale);

    glm::mat4x4 GetTransformationMatrix();

private:
    glm::vec3 m_position{};
    glm::vec3 m_scale{};
    glm::vec3 m_rotation{};
    std::shared_ptr<ObjectMesh<ShapeVertex>> m_objectMesh;
    std::shared_ptr<ShaderProgram> m_shaderProgram;
};

#endif //A3_SHAPE_H
