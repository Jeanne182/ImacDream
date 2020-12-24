#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>


void Terrain::display(const glm::mat4 &cameraView) {
    _objects[TREE].setPosition(glm::vec3(5.f, 0.f, -5.f));
    _objects[TREE].update(cameraView);

    _objects[SPHERE].setPosition(glm::vec3(0.5f, 0.f, -5.f));
    _objects[SPHERE].update(cameraView);

    _objects[TREE].setPosition(glm::vec3(-10.f, 0.f, -5.f));
    _objects[TREE].update(cameraView);

    _objects[RUNE].update(cameraView);
    _objects[HUT].update(cameraView);
    _objects[TERRAIN].update(cameraView);
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
    material.Ka = glm::vec4(1.f,1.f,1.f,1.f);
    material.Kd = glm::vec4(1.f,0.f,0.5f,1.f);
    material.Ks = glm::vec4(0.5f,0.5f,0.5f,0.5f);
    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indicesSphere.push_back(i);
        meshVerticesSphere.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    Model* sphereModel = new Model();
    sphereModel->_meshes.push_back(*sphereMesh);
    GameObject sphereObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereModel);
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = modelsPath + "/green_pine.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *tree);
    objects->push_back(treeObject);

    //TRUNK
    auto* trunk = new Model(modelsPath + "/trunk.obj");
    GameObject trunkObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *trunk);
    objects->push_back(trunkObject);

    //RUNE
    Model* rune = new Model(modelsPath + "/runejeanne.obj");
    GameObject runeObject(glm::vec3(-30.f,0.f,-5.f), 6.f, glm::vec3(90.f, 0.f, 0.f), *rune);
    objects->push_back(runeObject);

    //HUT
    Model* hut = new Model(modelsPath + "/Hut.obj");
    GameObject hutObject(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), *hut);
    objects->push_back(hutObject);

    //TERRAIN
    Model* terrain = new Model(modelsPath + "/terrain.obj");
    GameObject terrainObject(glm::vec3(0.f,-70.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *terrain);
    objects->push_back(terrainObject);


    _objects = *objects;
}



