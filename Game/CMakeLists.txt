cmake_minimum_required(VERSION 3.13)

project(IMACDream)

add_definitions(-std=c++11 -lSDL -lSDL2_mixer) # -Wall -W -Werror

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(Freetype REQUIRED)




# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR}  ${SDL_MIXER_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR}  ${FREETYPE_INCLUDE_DIRS} glimac/include third-party/include third-party)

set(ALL_LIBRARIES glimac ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_MIXER_LIBRARIES} ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} assimp)

add_subdirectory(glimac)

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/class/include/*.hpp)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/class/src/*.cpp)
file(GLOB SHADER_FILES ${CMAKE_SOURCE_DIR}/class/shaders/*.glsl)

set(OUTPUT ${PROJECT_NAME})
add_executable(${OUTPUT} ${HEADER_FILES} ${SRC_FILES} ${SHADER_FILES} class/src/StaticImage.cpp class/include/StaticImage.hpp)
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
