#include "../include/Terrain.hpp"
#include <glimac/Sphere.hpp>

Terrain::Terrain(std::vector<GameObject> &objects):
        _objects(objects){}

void Terrain::computeMatrix(const glm::mat4 &cameraView, glm::mat4 &projMatrix) {
    for(int i = 0; i < _objects.size(); i++){
        _objects[i].computeMatrix(cameraView, projMatrix);
    }
}

void Terrain::display(Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location) {
    for(int i = 0; i < _objects.size(); i++){
        _objects[i].display(program, M_Location, MV_Location, MVP_Location, N_Location);
    }
}

void Terrain::deleteBuffers() {
    for(int i = 0; i < _objects.size(); i++){
        _objects[i].deleteBuffers();
    }
}

std::vector<GameObject>* ObjectsManager(const FilePath &applicationPath){
    std::vector<GameObject>* objects = new std::vector<GameObject>;

    //SPHERE
    Sphere sphere(1,32,32);
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures);
    GameObject sphereObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereMesh);
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = applicationPath.dirPath() + "Assets/models/Arbol.obj";
    Model* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    objects->push_back(treeObject);

    return objects;
}