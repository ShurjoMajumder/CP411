//
// Created by shurj on 05-Nov-2024.
//

#ifndef A4_ASSETMANAGER_H
#define A4_ASSETMANAGER_H

#include <map>
#include <string>
#include <memory>

#include "ShaderProgram.h"

namespace Graphics {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager&) noexcept;
        AssetManager(AssetManager&&) noexcept;

        AssetManager& operator=(const AssetManager&) noexcept;
        AssetManager& operator=(AssetManager&&) noexcept;

        std::shared_ptr<ShaderProgram> LoadShader(const std::string&, const std::string&);

    private:
        std::map<std::string, std::shared_ptr<ShaderProgram>> m_programs;
    };
} // Graphics

#endif //A4_ASSETMANAGER_H
