cmake_minimum_required(VERSION 3.11)
project(a2)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# fetch external dependencies

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG f456deace7b408655109aaeff71421ef2d3858c6
)

FetchContent_Declare(
        glut
        GIT_REPOSITORY https://github.com/freeglut/freeglut.git
        GIT_TAG 566cd459201ae29003ef5686c06506d8646e55c6
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579
)

# GLEW configuration

set(glew_ONLY_LIBS ON CACHE INTERNAL "")
set(glew_BUILD_TESTS OFF CACHE INTERNAL "")
set(glew_BUILD_SHARED OFF CACHE INTERNAL "")

# GLUT configuration

set(FREEGLUT_BUILD_DEMOS OFF CACHE INTERNAL "")
set(FREEGLUT_BUILD_STATIC_LIBS ON INTERNAL "")
set(FREEGLUT_BUILD_SHARED_LIBS OFF INTERNAL "")

# GLFW configuration

set(GLFW_LIBRARY_TYPE STATIC CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(glm glew glut glfw)

# runtimes
add_executable(a2 SimpleDraw/src/main.cpp)

# linking
target_link_libraries(a2 PRIVATE glm::glm)
target_link_libraries(a2 PRIVATE libglew_static)
target_link_libraries(a2 PRIVATE freeglut)
target_link_libraries(a2 PRIVATE glfw)
