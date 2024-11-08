//
// Created by shurj on 05-Nov-2024.
//

#include <Graphics/Graphics.h>

#include "Shapes.h"
#include "Menu.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int argc, char** argv) {
    Graphics::WindowConfig config = {
            WINDOW_WIDTH, WINDOW_HEIGHT,
            100, 100,
            "SimpleView2",
            GLUT_RGB
    };

    Graphics::Init(argc, argv, config);

    Shapes::GenShapes(Graphics::GetWorld());

    Menu::Menu();

    Graphics::StartMainLoop();
}
