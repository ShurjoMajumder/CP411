cmake_minimum_required(VERSION 3.29)
project(a3)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(Transform2D Samples/opengl_transform2d.cpp)

target_link_libraries(Transform2D glew32s)
target_link_libraries(Transform2D freeglut)

add_executable(Transform3D Samples/opengl_transform3d.cpp)

target_link_libraries(Transform3D glew32s)
target_link_libraries(Transform3D freeglut)

add_executable(Mesh
        Mesh/src/Mesh.cpp
        Mesh/src/meshview.cpp
        Mesh/src/Point.cpp
        Mesh/src/Vector.cpp
)

target_link_libraries(Mesh glew32s)
target_link_libraries(Mesh freeglut)

add_executable(SimpleView SimpleView1/src/Matrix4x4.cpp SimpleView1/src/Matrix4x4.h
        SimpleView1/src/ShaderProgram.cpp
        SimpleView1/src/utils.cpp
        SimpleView1/src/SimpleView.cpp
        SimpleView1/src/Shape.cpp
        SimpleView1/src/Camera.cpp
        SimpleView1/src/World.cpp
        SimpleView1/src/Cube.cpp
        SimpleView1/src/Pyramid.cpp
        SimpleView1/src/House.cpp
        SimpleView1/src/Menu.cpp
)

target_link_libraries(SimpleView glew32s)
target_link_libraries(SimpleView freeglut)
target_link_libraries(SimpleView glfw3)
