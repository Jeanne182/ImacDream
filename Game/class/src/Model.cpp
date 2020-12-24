#include "./../include/Model.hpp"
#include <glimac/Image.hpp>
#include <vector>

namespace glimac {
    Model::Model() {}

    Model::Model(const std::string& path) {
        loadModel(path);
    }
    void Model::deleteBuffers(){
        for(unsigned int i = 0; i < _meshes.size(); i++)
            _meshes[i].deleteBuffers();
    }
    void Model::Draw()
    {
        for(unsigned int i = 0; i < _meshes.size(); i++)
            _meshes[i].Draw();
    }

    void Model::loadModel(std::string const &path)
    {
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // check for errors
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        // retrieve the directory path of the filepath
        this->_directory = path.substr(0, path.find_last_of('/'));
        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        // process all the node's _meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            _meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<ShapeVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            ShapeVertex vertex;
            glm::vec3 position;
            // positions
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;
            vertex.position = position;
            // normals
            if (mesh->HasNormals()) {
                position.x = mesh->mNormals[i].x;
                position.y = mesh->mNormals[i].y;
                position.z = mesh->mNormals[i].z;
                vertex.normal = position;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 texture;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                texture.x = mesh->mTextureCoords[0][i].x;
                texture.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = texture;
                /*// tangent
                position.x = mesh->mTangents[i].x;
                position.y = mesh->mTangents[i].y;
                position.z = mesh->mTangents[i].z;
                vertex.Tangent = position;
                // bitangent
                position.x = mesh->mBitangents[i].x;
                position.y = mesh->mBitangents[i].y;
                position.z = mesh->mBitangents[i].z;
                vertex.Bitangent = position;*/
            } else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // process _indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process material

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        Material mat;
        aiColor3D color;

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        mat.Ka = glm::vec4(color.r, color.g, color.b,1.0);
        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        mat.Kd = glm::vec4(color.r, color.g, color.b,1.0);
        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        mat.Ks = glm::vec4(color.r, color.g, color.b,1.0);

        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        return Mesh(vertices, indices, textures, mat);
    }

    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
            std::vector<Texture> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
                aiString str;
                mat->GetTexture(type, i, &str);
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), _directory);
                texture.type = typeName;
                texture.path = str.C_Str();

            textures.push_back(texture);
            }
            return textures;
        }

    unsigned int TextureFromFile(const char *path, const std::string &directory) {

        std::string filename = std::string(path);

        filename = directory + '/' + filename;

        FilePath filepath(filename);

        std::unique_ptr<Image> image = loadImage(filepath);
        if(image == nullptr){
            std::cerr << "Image" << filename << "could not be loaded" <<std::endl;
            return EXIT_FAILURE;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->getWidth() ,image->getHeight(),0,GL_RGBA,GL_FLOAT,
                     image->getPixels());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D,0);
        return texture;
    }

}
