cmake_minimum_required(VERSION 3.29)
project(c_cube C)

set(CMAKE_C_STANDARD 11)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(c_cube cube.c)
target_link_libraries(c_cube glew32s)
target_link_libraries(c_cube freeglut)


add_custom_command(TARGET c_cube POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:c_cube>                      # <-- this is the output path
)

