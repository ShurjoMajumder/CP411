//
// Created by shurj on 05-Nov-2024.
//

#ifndef A4_GRAPHICS_H
#define A4_GRAPHICS_H

#include <functional>
#include <ctime>

#include "AssetManager.h"
#include "Camera.h"
#include "CanvasItem.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "World.h"

namespace Graphics {
    struct WindowConfig {
        int Width;
        int Height;
        int PosX;
        int PosY;
        std::string Title;
        unsigned int DisplayMode;
    };

    void DisplayCallback();
    void DisplayResizeCallback(int width, int height);
    void MouseMotionCallback(GLint xMouse, GLint yMouse);
    void MouseActionCallback(int button, int state, int xMouse, int yMouse);
    void IdleCallback();

    void Init(int argc, char **argv, const WindowConfig& windowConfig);
    void StartMainLoop();
    void AddMouseMotionEvent(const std::function<void (int, int)>&);
    void AddMouseActionEvent(const std::function<void (int button, int state, int xMouse, int yMouse)>&);
    void AddIdleEvent(const std::function<void (double dt)>&);

    std::shared_ptr<World> GetWorld();
    std::shared_ptr<AssetManager> GetAssetManager();
    Camera& GetCamera();
    double GetDeltaTime();
}

#endif //A4_GRAPHICS_H
