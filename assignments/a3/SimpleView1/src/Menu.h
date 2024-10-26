//
// Created by shurj on 25-Oct-2024.
//

#pragma once

#ifndef A3_MENU_H
#define A3_MENU_H

#include <GL/glut.h>
#include "World.h"

void Menu();
void DisplayCallback();
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

#endif //A3_MENU_H
