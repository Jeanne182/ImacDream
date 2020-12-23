#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

   class ShapeVertex {
   public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

       inline ShapeVertex(): position(glm::vec3(0, 0, 0)), normal(glm::vec3(0, 0, 0)), texCoords(glm::vec2(0, 0)){}
       inline ShapeVertex(glm::vec3 C_position, glm::vec3 C_normal, glm::vec2 C_texCoords) : position(C_position), normal(C_normal), texCoords(C_texCoords){}

    };
    class Texture {
    public:
        GLuint id;
        std::string type;
        std::string path;
        inline Texture(): id(0), type(""), path(""){}
        inline Texture(GLuint C_id, std::string C_type, std::string C_path): id(C_id), type(C_type), path(C_path){}

    };

}
