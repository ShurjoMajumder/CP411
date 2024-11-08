//
// Created by shurj on 05-Nov-2024.
//

#include "Menu.h"

using namespace Graphics;

namespace Menu {
    struct {
        std::shared_ptr<CanvasItem> selectObj{};
        int csType{};
        int transType{};
        bool isInMove{};
        int xBegin{};
    } MenuData;

    enum MainMenuOptions {
        MAIN_MENU_RESET = 1,
        MAIN_MENU_QUIT  = 2
    };

    enum ObjectSelectMenuOptions {
        SELECT_CUBE    = 0,
        SELECT_PYRAMID = 1,
        SELECT_HOUSE   = 2
    };

    enum ModelTransformationOptions {
        MODEL_ROTATE_X = 1,
        MODEL_ROTATE_Y = 2,
        MODEL_ROTATE_Z = 3,
        MODEL_SCALE    = 4,
    };

    enum WorldTransformationOptions {
        WORLD_ROTATE_X    = 1,
        WORLD_ROTATE_Y    = 2,
        WORLD_ROTATE_Z    = 3,
        WORLD_TRANSLATE_X = 4,
        WORLD_TRANSLATE_Y = 5,
        WORLD_TRANSLATE_Z = 6
    };

    enum ViewTransformationOptions {
        CAMERA_PITCH = 1,
        CAMERA_ROLL = 2,
        CAMERA_YAW = 3,
        CAMERA_MOVE_LR = 4,
        CAMERA_MOVE_FB = 5,
        CAMERA_MOVE_UD = 6,
        CAMERA_ADJUST_NEAR = 7,
        CAMERA_ADJUST_FAR = 8,
    };

    enum TransformTarget {
        TRANSFORM_TARGET_MODEL = 1,
        TRANSFORM_TARGET_WORLD = 2,
        TRANSFORM_TARGET_CAMERA = 3
    };

    void Menu() {
        GLint Object_Menu = glutCreateMenu(ObjSubMenu);
        glutAddMenuEntry("Cube", SELECT_CUBE);
        glutAddMenuEntry("Pyramid", SELECT_PYRAMID);
        glutAddMenuEntry("House", SELECT_HOUSE);

        GLint MCTrans_Menu = glutCreateMenu(MCSTransMenu);
        glutAddMenuEntry("Rotate x", MODEL_ROTATE_X);
        glutAddMenuEntry("Rotate y", MODEL_ROTATE_Y);
        glutAddMenuEntry("Rotate z", MODEL_ROTATE_Z);
        glutAddMenuEntry("Scale", MODEL_SCALE);

        GLint WCTrans_Menu = glutCreateMenu(WCSTransMenu);
        glutAddMenuEntry("Rotate x", WORLD_ROTATE_X);
        glutAddMenuEntry("Rotate y", WORLD_ROTATE_Y);
        glutAddMenuEntry("Rotate z", WORLD_ROTATE_Z);
        glutAddMenuEntry("Translate x", WORLD_TRANSLATE_X);
        glutAddMenuEntry("Translate y", WORLD_TRANSLATE_Y);
        glutAddMenuEntry("Translate z", WORLD_TRANSLATE_Z);

        GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
        glutAddMenuEntry("Pitch", CAMERA_PITCH);
        glutAddMenuEntry("Roll", CAMERA_ROLL);
        glutAddMenuEntry("Yaw", CAMERA_YAW);
        glutAddMenuEntry("Move Left/Right", CAMERA_MOVE_LR);
        glutAddMenuEntry("Move Forwards/Back", CAMERA_MOVE_FB);
        glutAddMenuEntry("Move Up/Down", CAMERA_MOVE_UD);
        glutAddMenuEntry("Clipping Near (don't touch)", CAMERA_ADJUST_NEAR);
        glutAddMenuEntry("Clipping Far (don't touch)", CAMERA_ADJUST_FAR);

        glutCreateMenu(MainMenu);
        glutAddMenuEntry("Reset", MAIN_MENU_RESET);
        glutAddSubMenu("Select Object", Object_Menu);
        glutAddSubMenu("MCS Transformations", MCTrans_Menu);
        glutAddSubMenu("WCS Transformations", WCTrans_Menu);
        glutAddSubMenu("VCS Transformations", VCTrans_Menu);
        glutAddMenuEntry("Quit", MAIN_MENU_QUIT);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        Graphics::AddMouseActionEvent(MouseActionCallback);
        Graphics::AddMouseMotionEvent(MouseMotionCallback);

        MenuData.selectObj = Graphics::GetWorld()->SearchById(SELECT_CUBE);
        Graphics::GetCamera().Move({-3, -3, 0});
        Graphics::GetCamera().Yaw(-glm::pi<float>()/4, false);
    }

    void MouseActionCallback(int button, int state, int xMouse, int yMouse) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            MenuData.isInMove = true;
            MenuData.xBegin = xMouse;
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            MenuData.isInMove = false;
        }
        glutPostRedisplay();
    }

    void MouseMotionCallback(GLint xMouse, GLint yMouse) {
        if (!MenuData.isInMove) {
            return;
        }

        switch (MenuData.csType) {
            case TRANSFORM_TARGET_MODEL:
                MCSTransform(xMouse);
                break;
            case TRANSFORM_TARGET_WORLD:
                WCSTransform(xMouse);
                break;
            case TRANSFORM_TARGET_CAMERA:
                VCSTransform(xMouse);
                break;
            default:
                break;
        }

        glutPostRedisplay();
    }

    void MainMenu(GLint option) {
        switch (option) {
            case MAIN_MENU_RESET:
                Graphics::GetWorld()->Reset();
                Graphics::GetCamera().Move({-3, -3, 0});
                Graphics::GetCamera().Yaw(-glm::pi<float>()/4, false);
                Shapes::GenShapes(Graphics::GetWorld());
                break;
            case MAIN_MENU_QUIT:
                exit(0);
            default:
                break;
        }
    }

    void ObjSubMenu(GLint objectOption) {
        MenuData.selectObj = Graphics::GetWorld()->SearchById(objectOption);
        glutPostRedisplay();
    }

    void MCSTransMenu(GLint transOption) {
        MenuData.csType = TRANSFORM_TARGET_MODEL;
        MenuData.transType = transOption;
        glutPostRedisplay();
    }


    void WCSTransMenu(GLint transOption) {
        MenuData.csType = TRANSFORM_TARGET_WORLD;
        MenuData.transType = transOption;
        glutPostRedisplay();
    }

    void VCSTransMenu(GLint transOption) {
        MenuData.csType = TRANSFORM_TARGET_CAMERA;
        MenuData.transType = transOption;
        glutPostRedisplay();
    }

    void MCSTransform(GLint x) {
        GLfloat theta;
        theta = (MenuData.xBegin - x > 0) ? 1 : -1;
        theta *= (float)Graphics::GetDeltaTime() * 0.05f;

        switch (MenuData.transType) {
            case MODEL_ROTATE_X:
                MenuData.selectObj->Rotate(theta, 0, 0);
                break;
            case MODEL_ROTATE_Y:
                MenuData.selectObj->Rotate(0, theta, 0);
                break;
            case MODEL_ROTATE_Z:
                MenuData.selectObj->Rotate(0, 0, theta);
                break;
            case MODEL_SCALE:
                MenuData.selectObj->Scale(theta);
                break;
            default:
                break;
        }
    }

    void WCSTransform(GLint x) {
        GLfloat theta = (MenuData.xBegin - x > 0) ? -1 : 1;
        theta *= (float)Graphics::GetDeltaTime() * 0.02f;

        switch (MenuData.transType) {
            case WORLD_ROTATE_X:
                MenuData.selectObj->RotateOrigin({theta, 0, 0}, {0, 0, 0});
                break;
            case WORLD_ROTATE_Y:
                MenuData.selectObj->RotateOrigin({0, theta, 0}, {0, 0, 0});
                break;
            case WORLD_ROTATE_Z:
                MenuData.selectObj->RotateOrigin({0, 0, theta}, {0, 0, 0});
                break;
            case WORLD_TRANSLATE_X:
                MenuData.selectObj->Translate({theta, 0, 0});
                break;
            case WORLD_TRANSLATE_Y:
                MenuData.selectObj->Translate({0, theta, 0});
                break;
            case WORLD_TRANSLATE_Z:
                MenuData.selectObj->Translate({0, 0, theta});
                break;
            default:
                break;
        }
    }

    void VCSTransform(GLint x) {
        GLfloat theta = (MenuData.xBegin - x > 0) ? 1 : -1;
        theta *= (float)Graphics::GetDeltaTime() * 0.05f;
        Camera &camera = Graphics::GetCamera();

        if (MenuData.transType == CAMERA_PITCH) {
            //eye rotate x
            camera.Pitch(theta, false);
        }
        else if (MenuData.transType == CAMERA_ROLL) {
            // eye rotate y
            camera.Roll(theta);
        }
        else if (MenuData.transType == CAMERA_YAW) {
            //eye rotate z
            camera.Yaw(theta, false);
        }
        else if (MenuData.transType == CAMERA_MOVE_LR) {
            //eye translate x
            camera.Move({theta, 0.0, 0.0});
        }
        else if (MenuData.transType == CAMERA_MOVE_FB) {
            // eye translate y
            camera.Move({0.0, theta, 0.0});
        }
        else if (MenuData.transType == CAMERA_MOVE_UD) {
            // eye translate z
            camera.Move({0.0, 0.0, theta});
        }
        else if (MenuData.transType == 7) {  // change near plane
            camera.NearPlane += theta;
        }
        else if (MenuData.transType == 8) {  // change far plane
            camera.FarPlane += theta;
        }
    }
}
