cmake_minimum_required(VERSION 3.29)
project(shapes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

include_directories(C:/dev/CP411/include/)
link_directories(C:/dev/CP411/lib/Release/x64)

add_compile_definitions(NDEBUG)
add_compile_options(-DGLEW_STATIC)

add_executable(
        SimpleDraw SimpleDraw/src/simple_draw.cpp
        SimpleDraw/src/sd_callbacks.cpp
        SimpleDraw/src/sd_callbacks.h
        SimpleDraw/src/ShaderProgram.cpp
        SimpleDraw/src/ShaderProgram.h
        SimpleDraw/src/utils.cpp
        SimpleDraw/src/utils.h
        SimpleDraw/src/CanvasItemDequeue.cpp
        SimpleDraw/src/CanvasItemDequeue.h
        SimpleDraw/src/CanvasItem.cpp
        SimpleDraw/src/CanvasItem.h
)
target_link_libraries(SimpleDraw glew32s)
target_link_libraries(SimpleDraw freeglut)

add_executable(Primitives Primitives/src/opengl_primitives.c)
target_link_libraries(Primitives glew32s)
target_link_libraries(Primitives freeglut)

add_executable(Interactive Interactive/src/opengl_menu.cpp)
target_link_libraries(Interactive glew32s)
target_link_libraries(Interactive freeglut)

add_executable(Points Points/src/opengl_points.cpp)
target_link_libraries(Points glew32s)
target_link_libraries(Points freeglut)

add_executable(Key Key/src/opengl_key.cpp)
target_link_libraries(Key glew32s)
target_link_libraries(Key freeglut)

add_executable(Pick Pick/src/opengl_pick.cpp)
target_link_libraries(Pick glew32s)
target_link_libraries(Pick freeglut)

add_executable(Bitmap Bitmap/src/opengl_bitmap.cpp)
target_link_libraries(Bitmap glew32s)
target_link_libraries(Bitmap freeglut)

add_custom_command(TARGET SimpleDraw POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:SimpleDraw>                      # <-- this is the output path
)

add_custom_command(TARGET SimpleDraw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/dev/CP411/assignments/a2/SimpleDraw/src/quad.frag"
        $<TARGET_FILE_DIR:SimpleDraw>
)

add_custom_command(TARGET SimpleDraw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/dev/CP411/assignments/a2/SimpleDraw/src/general.vert"
        $<TARGET_FILE_DIR:SimpleDraw>
)

add_custom_command(TARGET Primitives POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:Primitives>                      # <-- this is the output path
)

add_custom_command(TARGET Interactive POST_BUILD            # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
        $<TARGET_FILE_DIR:Interactive>                      # <-- this is the output path
)

#add_custom_command(TARGET SimpleDraw POST_BUILD            # Adds a post-build event
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#        "C:/dev/CP411/bin/Release/x64/freeglut.dll"    # <-- target to copy
#        $<TARGET_FILE_DIR:SimpleDraw>                      # <-- this is the output path
#)
