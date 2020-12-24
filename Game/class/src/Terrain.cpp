#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>


void Terrain::display(const glm::mat4 &cameraView) {
    _objects[TREE].setPosition(glm::vec3(5.f, 0.f, -5.f));
    _objects[TREE].update(cameraView);

    _objects[SPHERE].setPosition(glm::vec3(0.5f, 0.f, -5.f));
    _objects[SPHERE].update(cameraView);

    _objects[TREE].setPosition(glm::vec3(-10.f, 0.f, -5.f));
    _objects[TREE].setScale(4.f);
    _objects[TREE].update(cameraView);
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
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    Model* sphereModel = new Model();
    sphereModel->_meshes.push_back(*sphereMesh);
    GameObject sphereObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereModel);
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = modelsPath + "/Arbol.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *tree);
    objects->push_back(treeObject);
    GameObject treeObject2(glm::vec3(8.f,-12.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[1]);
    objects->push_back(treeObject2);

    //TRUNK
    auto* trunk = new Model(modelsPath + "/trunk.obj");
    GameObject trunkObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *trunk);
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


    _objects = *objects;
}



