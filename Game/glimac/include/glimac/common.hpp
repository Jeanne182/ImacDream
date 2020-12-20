#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

    struct ShapeVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };
    struct Texture {
        GLuint id;
        std::string type;
        std::string path;
    };
    struct Material {
        //Material color lighting
        glm::vec4 Ka;
        //Diffuse reflection
        glm::vec4 Kd;
        //Mirror reflection
        glm::vec4 Ks;
    };
}
