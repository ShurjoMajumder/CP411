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

#include "CanvasItem.h"
#include "Camera.h"

namespace Graphics {
    class World {
    public:
        World();
        World(int screenWidth, int screenHeight);

        ~World();
        World(const World &other);
        World(World &&other) noexcept;

        World& operator=(const World &other) noexcept;
        World& operator=(World &&other) noexcept;

        int GetWindowWidth() const;
        int GetWindowHeight() const;
        void ResizeWindow(int width, int height);

        void Draw() const;

        void AddCanvasItem(const std::shared_ptr<CanvasItem>& canvasItem);
        std::shared_ptr<CanvasItem> SearchById(int i);

        Camera& GetCamera();

        void Reset();

    private:
        int m_screenWidth = 0, m_screenHeight = 0;
        std::vector<std::shared_ptr<CanvasItem>> m_canvasItems{};
        Camera m_camera{};
    };
}

#endif //A3_WORLD_H
