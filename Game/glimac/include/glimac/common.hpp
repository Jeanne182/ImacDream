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

}
