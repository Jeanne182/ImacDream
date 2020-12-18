//
// Created by matteo on 14/12/2020.
//

#ifndef IMACDREAM_MODEL_HPP
#define IMACDREAM_MODEL_HPP

#include <glimac/Program.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "./Mesh.hpp"

namespace glimac {

    class Model {
    public:
        Model(const std::string& path);
        void deleteBuffers();
        void Draw(Program &program);

    public:
        // model data
        std::vector<Mesh> _meshes;
        std::string _directory;


        void loadModel(const std::string &path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);


    };


    unsigned int TextureFromFile(const char *path, const std::string &directory);
}
#endif //IMACDREAM_MODEL_HPP
