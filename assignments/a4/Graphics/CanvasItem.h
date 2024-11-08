//
// Created by shurj on 05-Nov-2024.
//

#ifndef A4_CANVASITEM_H
#define A4_CANVASITEM_H

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

#include "ShaderProgram.h"
#include "Mesh.h"

namespace Graphics {
    struct CanvasItemVertex {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    class CanvasItem {
    public:
        CanvasItem(const std::shared_ptr<Mesh<CanvasItemVertex>> &, const std::shared_ptr<ShaderProgram> &);
        ~CanvasItem();

        const std::shared_ptr<ShaderProgram>& GetShaderProgram() const;

        void Draw() const;
        void Reset();

        void Translate(glm::vec3 xyz);
        void Rotate(float rx, float ry, float rz);
        void RotateOrigin(glm::vec3 rxryrz, glm::vec3 origin);
        void Scale(float scale);

        glm::mat4x4 GetTransformationMatrix() const;

    private:
        glm::vec3 m_position{};
        glm::vec3 m_scale{};
        glm::vec3 m_rotation{};
        std::shared_ptr<ShaderProgram> m_program;
        std::shared_ptr<Mesh<CanvasItemVertex>> m_mesh;
    };
}

#endif //A4_CANVASITEM_H
