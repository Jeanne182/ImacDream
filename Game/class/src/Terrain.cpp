#include "../include/Terrain.hpp"
#include <glimac/Sphere.hpp>


void Terrain::display(const glm::mat4 &cameraView, glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location) {

    _objects[0].setPosition(glm::vec3(0.5f, 0.f, -5.f));
    _objects[0].update(cameraView, projMatrix, program, M_Location, MV_Location, MVP_Location, N_Location);

    _objects[0].setPosition(glm::vec3(-5.f, 0.f, -4.f));
    _objects[0].setScale(2.f);
    _objects[0].update(cameraView, projMatrix, program, M_Location, MV_Location, MVP_Location, N_Location);
}

void Terrain::deleteBuffers() {
    for(auto & _object : _objects){
        _object.deleteBuffers();
    }
}

void Terrain::ObjectsManager(const FilePath &applicationPath){
    auto* objects = new std::vector<GameObject>;

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
    std::string pathModelTree = applicationPath.dirPath() + "Assets/models/Arbol.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    objects->push_back(treeObject);

    //TRUNK
    auto* trunk = new Model(applicationPath.dirPath() + "Assets/models/trunk.obj");
    GameObject trunkObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), trunk->_meshes[0]);
    objects->push_back(trunkObject);

    _objects = *objects;
}



