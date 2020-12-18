//
// Created by matteo on 14/12/2020.
//

#ifndef IMACDREAM_MESH_HPP
#define IMACDREAM_MESH_HPP

//#pragma once
#include <glimac/Program.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glimac/common.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace glimac {

    class Mesh {
    public:
        // mesh data
        std::vector<ShapeVertex> _vertices;
        std::vector<GLuint> _indices;
        std::vector<Texture> _textures;

        // constructor
        Mesh(std::vector<ShapeVertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures):
        _vertices(vertices), _indices(indices), _textures(textures)
        {
            // now that we have all the required data, set the vertex buffers and its attribute pointers.
            setupMesh();
        };
        void deleteBuffers();
        void Draw(Program &program) const;
        //void Draw(Program &program);


    public:
        //  render data
        unsigned int _vao, _vbo, _ibo;

        void setupMesh();
    };
}




#endif //IMACDREAM_MESH_HPP
