cmake_minimum_required(VERSION 3.29)
project(a3)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_executable(a3 main.cpp)

target_link_libraries(a3 glew32s)
target_link_libraries(a3 freeglut)

add_executable(Transform2D Samples/opengl_transform2d.cpp)

target_link_libraries(Transform2D glew32s)
target_link_libraries(Transform2D freeglut)
