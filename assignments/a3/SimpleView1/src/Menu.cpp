//
// Created by shurj on 25-Oct-2024.
//

#include <memory>

#include "World.h"
#include "Camera.h"
#include "Menu.h"

struct {
    std::shared_ptr<Shape> selectObj{};
    World world{800, 800};
    int csType{};
    int transType{};
    bool isInMove;
    int xbegin;
} MenuData;

void Menu() {
    GLint Object_Menu = glutCreateMenu(ObjSubMenu);
    glutAddMenuEntry("Cube", 0);
    glutAddMenuEntry("Pyramid", 1);
    glutAddMenuEntry("House", 2);

    GLint MCTrans_Menu = glutCreateMenu(MCSTransMenu);
    glutAddMenuEntry("Rotate x", 1);
    glutAddMenuEntry("Rotate y", 2);
    glutAddMenuEntry("Rotate z", 3);
    glutAddMenuEntry("Scale", 4);

    GLint WCTrans_Menu = glutCreateMenu(WCSTransMenu);
    glutAddMenuEntry("Rotate x", 1);
    glutAddMenuEntry("Rotate y", 2);
    glutAddMenuEntry("Rotate z", 3);
    glutAddMenuEntry("Translate x", 4);
    glutAddMenuEntry("Translate y", 5);
    glutAddMenuEntry("Translate z", 6);

    GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
    glutAddMenuEntry("Rotate x", 1);
    glutAddMenuEntry("Rotate y", 2);
    glutAddMenuEntry("Rotate z", 3);
    glutAddMenuEntry("Translate x", 4);
    glutAddMenuEntry("Translate y", 5);
    glutAddMenuEntry("Translate z", 6);
    glutAddMenuEntry("Clipping Near", 7);
    glutAddMenuEntry("Clipping Far", 8);

    glutCreateMenu(MainMenu);
    glutAddMenuEntry("Reset", 1);
    glutAddSubMenu("Select Object", Object_Menu);
    glutAddSubMenu("MCS Transformations", MCTrans_Menu);
    glutAddSubMenu("WCS Transformations", WCTrans_Menu);
    glutAddSubMenu("VCS Transformations", VCTrans_Menu);
    glutAddMenuEntry("Quit", 2);
}

void DisplayCallback() {
    MenuData.world.Draw();  // this gives me physical pain
}

void MouseActionCallback(int button, int state, int xMouse, int yMouse) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        MenuData.isInMove = true;
        MenuData.xbegin = xMouse;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        MenuData.isInMove = false;
    }
}

void MouseMotionCallback(GLint xMouse, GLint yMouse) {
    if (MenuData.isInMove) {
        if (MenuData.csType == 1){     //  Model transformations
            MCSTransform(xMouse);
        }
        else if (MenuData.csType == 2){ // WCS transformations
            WCSTransform(xMouse);
        }
        else if(MenuData.csType == 3){ // VCS transformations
            VCSTransform(xMouse);
        }
        glutPostRedisplay();
    }
}

void MainMenu(GLint option) {
    switch (option) {
        case 1:
            MenuData.world.Reset();
            break;
        case 2:
            exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}

void ObjSubMenu(GLint objectOption)
{
    MenuData.selectObj = MenuData.world.SearchById(objectOption);
    glutPostRedisplay();
}


void MCSTransMenu(GLint transOption) {
    MenuData.csType = 1;
    MenuData.transType = transOption;
    glutPostRedisplay();
}


void WCSTransMenu(GLint transOption) {
    MenuData.csType = 2;
    MenuData.transType = transOption;
    glutPostRedisplay();
}

void VCSTransMenu(GLint transOption) {
    MenuData.csType = 3;
    MenuData.transType = transOption;
    glutPostRedisplay();
}

void MCSTransform(GLint x) {
    GLfloat theta;
    theta = (MenuData.xbegin - x > 0) ? 1 : -1;
    theta *= 0.5f;

    if (MenuData.transType == 1) { //model rotate x
        MenuData.selectObj->Rotate(theta, 0, 0);
    } else if (MenuData.transType == 2) { //model rotate y
        MenuData.selectObj->Rotate(0, theta, 0);
    } else if (MenuData.transType == 3){  //model rotate z
        MenuData.selectObj->Rotate(0, 0, theta);
    } else if (MenuData.transType == 4) { //model scale
        MenuData.selectObj->Scale(theta);
    }
}

void WCSTransform(GLint x) {
    GLfloat theta = (MenuData.xbegin - x > 0) ? 1 : -1;
    if (MenuData.transType == 1) {  // rotate x
        MenuData.selectObj->RotateOrigin({0.5f * theta, 0, 0}, {0, 0, 0});
    }
    else if (MenuData.transType == 2) {
        MenuData.selectObj->RotateOrigin({0, 0.5f * theta, 0}, {0, 0, 0});
    }
    else if(MenuData.transType == 3) {
        MenuData.selectObj->RotateOrigin({0, 0, 0.5f * theta}, {0, 0, 0});
    }
    else if (MenuData.transType == 4) {
        MenuData.selectObj->Translate({theta * 0.02, 0, 0});
    }
    else if(MenuData.transType == 5){ //WC translate y
        MenuData.selectObj->Translate({0, theta * 0.02, 0});
    }
    else if(MenuData.transType == 6){ //WC translate z
        MenuData.selectObj->Translate({0, 0, theta * 0.02});
    }
}

void VCSTransform(GLint x) {
    GLfloat theta = (MenuData.xbegin - x > 0) ? 1 : -1;
    Camera &myCamera = MenuData.world.GetCamera();
    if (MenuData.transType == 1) {  //eye rotate x
        myCamera.Pitch(theta*0.5f, false);
    }
    else if (MenuData.transType == 2) { // eye rotate y
        myCamera.Roll(theta*0.5f);
    }
    else if(MenuData.transType == 3){ //eye rotate z
        myCamera.Yaw(theta*0.5f, false);
    }
    else if (MenuData.transType == 4) { //eye translate x
        myCamera.Move({theta * 0.02, 0.0, 0.0});
    }
    else if(MenuData.transType == 5){   // eye translate y
        myCamera.Move({0.0, theta * 0.02, 0.0});
    }
    else if(MenuData.transType == 6){ // eye translate z
        myCamera.Move({0.0, 0.0, theta * 0.02});
    }
    else if(MenuData.transType == 7){  // change dnear
        myCamera.m_nearPlane += theta * .1f;
    }
    else if(MenuData.transType == 8){  // change dfar
        myCamera.m_farPlane += theta * .1f;
    }
}
