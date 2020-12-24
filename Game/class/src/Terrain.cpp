#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>


void Terrain::display(const glm::mat4 &cameraView) {

    _objects[1].setPosition(glm::vec3(0.5f, 0.f, -5.f));
    _objects[1].update(cameraView);

    _objects[1].setPosition(glm::vec3(-5.f, 0.f, -4.f));
    _objects[1].setScale(2.f);
    _objects[1].update(cameraView);
}

void Terrain::deleteBuffers() {
    for(auto & _object : _objects){
        _object.deleteBuffers();
    }
}

void Terrain::ObjectsManager() {
    auto* objects = new std::vector<GameObject>;
    std::string modelsPath = AssetManager::Get()->appPath().dirPath() + "Assets/models";

    //SPHERE
    Sphere sphere(1,32,32);
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    Material material;

    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    GameObject sphereObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereMesh);
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = modelsPath + "/Arbol.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    objects->push_back(treeObject);

    //TRUNK
    auto* trunk = new Model(modelsPath + "/trunk.obj");
    GameObject trunkObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), trunk->_meshes[0]);
    objects->push_back(trunkObject);

    _objects = *objects;
}



