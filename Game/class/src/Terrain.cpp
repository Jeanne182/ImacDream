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
    std::vector<GLuint> indicesSphere;
    std::vector<Texture> texturesSphere;
    std::vector<ShapeVertex> meshVerticesSphere;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indicesSphere.push_back(i);
        meshVerticesSphere.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVerticesSphere, indicesSphere, texturesSphere);
    GameObject sphereObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereMesh);
    objects->push_back(sphereObject);

    //TREE
    /*std::string pathModelTree = applicationPath.dirPath() + "Assets/models/Arbol.obj";
    Model* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    objects->push_back(treeObject);*/

/*
    //CUBE
    std::vector<GLuint> indicesCube;
    std::vector<Texture> texturesCube;
    std::vector<ShapeVertex> meshVerticesCube = {
    ShapeVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 0)),//0
    ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//1
    ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//2
    ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//3
    ShapeVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//4
    ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//5
    ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//6
    ShapeVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0))};//7


    indicesCube = {
      0, 1, 2,
      0, 1, 4,//haut
      0, 4, 3,
      4, 3, 6,//face
      4, 1, 6,
      1, 6, 5,//droite
      0, 2, 3,
      2, 3, 7,//gauche
      2, 1, 5,
      2, 5, 7,//dos
      7, 5, 3,
      5, 3, 6//bas
    };


    Mesh* cubeMesh = new Mesh(meshVerticesCube, indicesCube, texturesCube);
    GameObject cubeObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *cubeMesh);
    objects->push_back(cubeObject);

*/

    return objects;
}

