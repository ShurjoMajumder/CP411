cmake_minimum_required(VERSION 3.29)
project(gravity)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# fetch external dependencies

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG glew-cmake-2.2.0
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

# GLEW configuration

set(glew_ONLY_LIBS ON CACHE INTERNAL "")
set(glew_BUILD_TESTS OFF CACHE INTERNAL "")
set(glew_BUILD_SHARED OFF CACHE INTERNAL "")

# GLFW configuration

set(GLFW_LIBRARY_TYPE STATIC CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(glm glew glfw)

add_executable(gravity main.cpp
        Graphics/ShaderProgram.cpp
        Graphics/ShaderProgram.h
        Graphics/utils.cpp
        Graphics/AssetManager.cpp
        Graphics/AssetManager.h
        Simulation/Particle.cpp
        Simulation/Particle.h
        Simulation/World.cpp
        Simulation/World.h
        Simulation/Forces.cpp
        Simulation/Forces.h
)

target_link_libraries(gravity PRIVATE glm::glm)
target_link_libraries(gravity PRIVATE libglew_static)
target_link_libraries(gravity PRIVATE glfw)
