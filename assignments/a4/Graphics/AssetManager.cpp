//
// Created by shurj on 05-Nov-2024.
//

#include "AssetManager.h"

namespace Graphics {
    AssetManager::AssetManager() : m_programs() {}

    AssetManager::~AssetManager() = default;

    AssetManager::AssetManager(const AssetManager &other) noexcept {
        m_programs = other.m_programs;
    }

    AssetManager::AssetManager(AssetManager &&other) noexcept {
        m_programs = std::move(other.m_programs);
    }

    AssetManager &AssetManager::operator=(const AssetManager &other) noexcept {
        m_programs = other.m_programs;

        return *this;
    }

    AssetManager &AssetManager::operator=(AssetManager &&other) noexcept {
        m_programs = std::move(other.m_programs);

        return *this;
    }

    std::shared_ptr<ShaderProgram> AssetManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath) {
        auto program = std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
        m_programs.insert({vertexPath + fragmentPath, program});

        return program;
    }
} // Graphics
