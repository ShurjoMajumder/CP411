cmake_minimum_required(VERSION 3.29)
project(shapes)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_C_STANDARD 17)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)
add_executable(SimpleDraw SimpleDraw/src/main.cpp)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)
target_link_libraries(SimpleDraw glew32s)
target_link_libraries(SimpleDraw freeglut)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)
add_executable(primitives Primitives/src/opengl_primitives.c)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)
target_link_libraries(primitives glew32s)
target_link_libraries(primitives freeglut)

add_custom_command(TARGET primitives POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:primitives>                      # <-- this is the output path
)

add_custom_command(TARGET SimpleDraw POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:SimpleDraw>                      # <-- this is the output path
)
