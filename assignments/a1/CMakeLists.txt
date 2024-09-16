cmake_minimum_required(VERSION 3.29)
project(shapes)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(shapes glut_test.cpp)
target_link_libraries(shapes glew32s)
target_link_libraries(shapes freeglut)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(blender
        blender.c)

add_custom_command(TARGET shapes POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:shapes>                          # <-- this is the output path
)
