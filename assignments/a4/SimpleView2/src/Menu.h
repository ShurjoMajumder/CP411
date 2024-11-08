//
// Created by shurj on 05-Nov-2024.
//

#ifndef A4_MENU_H
#define A4_MENU_H

#include <Graphics/Graphics.h>

#include "Shapes.h"

namespace Menu {
    void Menu();
    void MouseActionCallback(int button, int state, int xMouse, int yMouse);
    void MouseMotionCallback(GLint xMouse, GLint yMouse);
    void MainMenu(GLint option);
    void ObjSubMenu(GLint objectOption);
    void MCSTransMenu(GLint transOption);
    void WCSTransMenu(GLint transOption);
    void VCSTransMenu(GLint transOption);
    void MCSTransform(GLint);
    void WCSTransform(GLint);
    void VCSTransform(GLint);
}

#endif //A4_MENU_H
