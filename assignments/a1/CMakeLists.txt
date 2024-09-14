cmake_minimum_required(VERSION 3.29)
project(a1)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(NDEBUG)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_executable(a1 main.cpp)
target_link_libraries(a1 glew32s)
target_link_libraries(a1 freeglut)

add_custom_command(TARGET a1 POST_BUILD                # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:a1>                          # <-- this is the output path
)
