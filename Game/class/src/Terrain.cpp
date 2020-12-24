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
    Material material;
    material.Ka = glm::vec4(1.f,1.f,1.f,1.f);
    material.Kd = glm::vec4(1.f,0.f,0.5f,1.f);
    material.Ks = glm::vec4(0.5f,0.5f,0.5f,0.5f);
    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    GameObject sphereObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereMesh);
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = applicationPath.dirPath() + "Assets/models/green_pine.obj";
    Model* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(8.f,-12.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    objects->push_back(treeObject);
    GameObject treeObject2(glm::vec3(8.f,-12.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[1]);
    objects->push_back(treeObject2);

    //TRUNK
    Model* trunk = new Model(applicationPath.dirPath() + "Assets/models/trunk.obj");
    GameObject trunkObject(glm::vec3(-30.f,0.f,-5.f), 6.f, glm::vec3(0.f, 0.f, 0.f), trunk->_meshes[0]);
    objects->push_back(trunkObject);

    //RUNE
    Model* rune = new Model(applicationPath.dirPath() + "Assets/models/runejeanne.obj");
    GameObject runeObject(glm::vec3(-30.f,0.f,-5.f), 6.f, glm::vec3(90.f, 0.f, 0.f), rune->_meshes[0]);
    objects->push_back(runeObject);

    //HUT
    Model* hut = new Model(applicationPath.dirPath() + "Assets/models/Hut.obj");
    GameObject hutObject(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), hut->_meshes[0]);
    objects->push_back(hutObject);
    GameObject hutObject1(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), hut->_meshes[1]);
    objects->push_back(hutObject1);
    GameObject hutObject2(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), hut->_meshes[2]);
    objects->push_back(hutObject2);
    GameObject hutObject3(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), hut->_meshes[3]);
    objects->push_back(hutObject3);

    //TERRAIN
    Model* terrain = new Model(applicationPath.dirPath() + "Assets/models/terrain.obj");
    GameObject terrainObject(glm::vec3(0.f,-70.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), terrain->_meshes[0]);
    objects->push_back(terrainObject);


    return objects;
}