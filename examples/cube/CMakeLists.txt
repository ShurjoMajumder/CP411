cmake_minimum_required(VERSION 3.29)
project(cube)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/dev/CP411/include/")
link_directories("C:/dev/CP411/lib/Release/x64")

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(cube
        example6.cpp
        InitShader.cpp
)

target_link_libraries(cube glew32s)
target_link_libraries(cube freeglut)

add_custom_command(TARGET cube POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:cube>                          # <-- this is the output path
)

add_custom_command(TARGET cube POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/examples/cube/vshader36.glsl"    # <-- target to copy
        $<TARGET_FILE_DIR:cube>                          # <-- this is the output path
)

add_custom_command(TARGET cube POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/examples/cube/fshader36.glsl"    # <-- target to copy
        $<TARGET_FILE_DIR:cube>                          # <-- this is the output path
)
