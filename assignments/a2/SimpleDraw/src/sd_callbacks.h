//
// Created by shurj on 28-Sep-2024.
//

#pragma once

#ifndef SHAPES_SD_CALLBACKS_H
#define SHAPES_SD_CALLBACKS_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "sd_callbacks.h"
#include "ShaderProgram.h"

namespace SimpleDraw {

    const float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    void init();  // initializes the program.

    void display_callback();    // display callback in the main loop.
    void mouse_callback();      // callback for handling mouse events.
    void main_menu_callback();  // callback for handling the main menu.

    void cleanup();
}

#endif //SHAPES_SD_CALLBACKS_H
