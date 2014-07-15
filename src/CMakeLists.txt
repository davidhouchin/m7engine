project(m7engine)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST/src)
add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(/usr/include/sdl2)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_gfx SDL2_mixer)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra ${CMAKE_CXX_FLAGS}")
