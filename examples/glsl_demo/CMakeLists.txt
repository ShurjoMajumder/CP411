cmake_minimum_required(VERSION 3.29)
project(glsl_demo)

set(CMAKE_CXX_STANDARD 98)

add_compile_definitions(NDEBUG)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_executable(glsl_demo
        glApplication.cpp
        glsl.cpp
        glutWindow.cpp
        glWindow.cpp
        main.cpp
)

target_link_libraries(glsl_demo glew32s)
target_link_libraries(glsl_demo freeglut)

add_custom_command(TARGET glsl_demo POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:glsl_demo>                          # <-- this is the output path
)
