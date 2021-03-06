cmake_minimum_required(VERSION 3.13)

project(IMACDream)

add_definitions(-std=c++17 ) # -Wall -W -Werror
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Freetype REQUIRED)


# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR}  ${FREETYPE_INCLUDE_DIRS} glimac/include third-party/include third-party)

set(ALL_LIBRARIES glimac ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES})

add_subdirectory(glimac)
add_compile_options( -Wall -W -Werror)

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/class/include/*.hpp)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/class/src/*.cpp)
file(GLOB SHADER_FILES ${CMAKE_SOURCE_DIR}/class/shaders/*.glsl)

set(OUTPUT ${PROJECT_NAME})
add_executable(${OUTPUT} ${HEADER_FILES} ${SRC_FILES} ${SHADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES} -lSDL2 -lSDL2main -lSDL2_mixer)
