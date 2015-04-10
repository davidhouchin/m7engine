project(m7engine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb ${CMAKE_CXX_FLAGS}")

aux_source_directory(./src GAME_SRC)
aux_source_directory(./src/engine ENGINE_SRC)

add_executable(${PROJECT_NAME} ${GAME_SRC} ${ENGINE_SRC})

#Check if OSX, expects homebrew installed SDL2
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	include_directories(/usr/local/include)
	target_link_libraries(${PROJECT_NAME} /usr/local/lib/libSDL2.dylib /usr/local/lib/libSDL2_image.dylib /usr/local/lib/libSDL2_ttf.dylib /usr/local/lib/libSDL2_mixer.dylib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#Check if Linux, expects standard apt/yum installed SDL2
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	include_directories(/usr/include/sdl2)
	target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#Check if Windows, expects MinGW installed SDL2
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include_directories(C:/MinGW/include/SDL2)
	target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -Wl,-subsystem,windows ${CMAKE_CXX_FLAGS}")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
