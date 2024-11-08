cmake_minimum_required(VERSION 3.29)
project(a4)

set(CMAKE_CXX_STANDARD 11)

include_directories(C:/dev/CP411/include/)
include_directories(C:/dev/CP411/assignments/a4)
link_directories(C:/dev/CP411/lib/Release/x64)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(opengl_culling Samples/opengl_culling.cpp)
target_link_libraries(opengl_culling glew32s)
target_link_libraries(opengl_culling freeglut)

add_executable(opengl_cube_draw Samples/opengl_draw_cube.cpp)
target_link_libraries(opengl_cube_draw glew32s)
target_link_libraries(opengl_cube_draw freeglut)

add_executable(opengl_simple_light Samples/opengl_simple_light.cpp)
target_link_libraries(opengl_simple_light glew32s)
target_link_libraries(opengl_simple_light freeglut)

add_executable(opengl_move_light Samples/opengl_move_light.cpp)
target_link_libraries(opengl_move_light glew32s)
target_link_libraries(opengl_move_light freeglut)

add_library(graphics STATIC
        Graphics/Camera.cpp
        Graphics/ShaderProgram.cpp
        Graphics/utils.cpp
        Graphics/World.cpp
        Graphics/Graphics.cpp
        Graphics/CanvasItem.cpp
        Graphics/AssetManager.cpp
        Graphics/Mesh.h
)

add_executable(SimpleView
        SimpleView2/src/SimpleView.cpp
        SimpleView2/src/Cube.cpp
        SimpleView2/src/House.cpp
        SimpleView2/src/Pyramid.cpp
        SimpleView2/src/Menu.cpp
        SimpleView2/src/Shapes.cpp
        SimpleView2/src/Shapes.h
        SimpleView2/src/Axes.cpp
        SimpleView2/src/Axes.h
)

target_link_libraries(SimpleView graphics)
target_link_libraries(SimpleView glew32s)
target_link_libraries(SimpleView freeglut)

