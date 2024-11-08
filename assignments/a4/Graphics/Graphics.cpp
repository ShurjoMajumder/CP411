//
// Created by shurj on 05-Nov-2024.
//

#include "Graphics.h"


namespace Graphics {
    struct {
        double dt{}, oldTime{};

        std::shared_ptr<World> world;
        std::shared_ptr<AssetManager> assetManager;

        // Event callback lists. std::function is used in order to allow for lambda functions, and callable objects,
        // instead of just function pointers.
        std::vector<std::function<void (GLint, GLint)>> mouseMotionCallbacks;
        std::vector<std::function<void (int, int, int, int)>> mouseActionCallbacks;
        std::vector<std::function<void (double)>> idleCallbacks;
    } GraphicsData;

    void Init(int argc, char **argv, const WindowConfig& windowConfig) {
        glutInit(&argc, argv);
        glutInitDisplayMode(windowConfig.DisplayMode);
        glutInitWindowPosition(windowConfig.PosX, windowConfig.PosY);
        glutInitWindowSize(windowConfig.Width, windowConfig.Height);
        glutCreateWindow(windowConfig.Title.c_str());

        glewInit();

        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        // acquire and initialize resources
        GraphicsData.mouseMotionCallbacks = {};
        GraphicsData.mouseActionCallbacks = {};
        GraphicsData.idleCallbacks = {};
        GraphicsData.oldTime = clock();

        glutReshapeFunc(DisplayResizeCallback);
        glutDisplayFunc(DisplayCallback);
        glutMotionFunc(MouseMotionCallback);
        glutMouseFunc(MouseActionCallback);
        glutIdleFunc(IdleCallback);

        GraphicsData.world = std::make_shared<World>(windowConfig.Width, windowConfig.Height);
        GraphicsData.assetManager = std::make_shared<AssetManager>();
    }

    void AddMouseMotionEvent(const std::function<void(int, int)>& event) {
        GraphicsData.mouseMotionCallbacks.push_back(event);
    }

    void AddMouseActionEvent(const std::function<void(int, int, int, int)>& event) {
        GraphicsData.mouseActionCallbacks.push_back(event);
    }

    void AddIdleEvent(const std::function<void(double)> &event) {
        GraphicsData.idleCallbacks.push_back(event);
    }

    void StartMainLoop() {
        glutMainLoop();
    }

    void DisplayCallback() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

        GraphicsData.world->Draw();
        glutSwapBuffers();
    }

    void DisplayResizeCallback(int width, int height) {
        glViewport(0, 0, width, height);
        GraphicsData.world->ResizeWindow(width, height);
    }

    void MouseMotionCallback(GLint xMouse, GLint yMouse) {
        // Forward arguments to registered listeners.
        // Modern C++ FTW.
        for (const auto& callback : GraphicsData.mouseMotionCallbacks) {
            callback(xMouse, yMouse);
        }
    }

    void MouseActionCallback(int button, int state, int xMouse, int yMouse) {
        for (const auto& callback : GraphicsData.mouseActionCallbacks) {
            callback(button, state, xMouse, yMouse);
        }
    }

    void IdleCallback() {
        double currentTime = clock();
        GraphicsData.dt = currentTime - GraphicsData.oldTime;
        GraphicsData.oldTime = currentTime;

        for (const auto& callback : GraphicsData.idleCallbacks) {
            callback(GraphicsData.dt);
        }

        glutPostRedisplay();
    }

    std::shared_ptr<World> GetWorld() {
        return GraphicsData.world;
    }

    std::shared_ptr<AssetManager> GetAssetManager() {
        return GraphicsData.assetManager;
    }

    Camera& GetCamera() {
        return GraphicsData.world->GetCamera();
    }

    double GetDeltaTime() {
        return GraphicsData.dt;
    }
}
