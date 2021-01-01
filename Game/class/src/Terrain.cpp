#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>

void Terrain::setMapTerrain() {
    glm::vec3 minVector;
    for(auto meshes : _objects[TERRAIN]._model->_meshes){
        for(auto vertices : meshes._vertices){
            _mapTerrain[std::make_tuple(vertices.position.x*100, vertices.position.z*100)] = vertices.position.y;
        }
    }
}

/*
float Terrain::getTerrainHeight(const float x, const float z){
    std::map<std::tuple<int, int>, float>::iterator low, prev;
    std::tuple<int, int> pos = std::tuple<int, int>(x*100, z*100);
    low = _mapTerrain.lower_bound(pos);
    if (low == _mapTerrain.end()) {
        std::cout << "Position not find" << std::endl;
    }
    else if (low == _mapTerrain.begin()) {
        std::cout << "low= " << std::get<0>(low->first) << " & " << std::get<1>(low->first) << std::endl;
        return low->second;
    }
    else {
        prev = std::prev(low);
        if ((std::get<0>(pos) - std::get<0>(prev->first) && std::get<1>(pos) - std::get<1>(prev->first)) < (std::get<0>(low->first) - std::get<0>(pos) && std::get<1>(low->first) - std::get<1>(pos))){
            std::cout << "prev= " << std::get<0>(prev->first)/100 << " & " << std::get<1>(prev->first)/100 << std::endl;
            std::cout << "y= " << prev->second << std::endl;
            return prev->second;
        }

        else{
            std::cout << "low= " << std::get<0>(low->first)/100 << " & " << std::get<1>(low->first)/100 << std::endl;
            std::cout << "y= " << low->second << std::endl;
            return low->second;
        }
    }
    return 5.f;
}
*/
void Terrain::display(const glm::mat4 &cameraView) {
    //setMapTerrain();
    _objects[TREE].setPosition(glm::vec3(5.f, 0.f, -5.f));
    _objects[TREE].setCenter();
    _objects[TREE].setHitboxRadius();
    _objects[TREE].update(cameraView);

    _objects[SPHERE].setPosition(glm::vec3(0.5f, 0.f, -5.f));
    _objects[SPHERE].setCenter();
    _objects[SPHERE].setHitboxRadius();
    _objects[SPHERE].update(cameraView);

    _objects[TREE].setPosition(glm::vec3(-10.f, 0.f, -5.f));
    _objects[TREE].setCenter();
    _objects[TREE].setHitboxRadius();
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
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    Model* sphereModel = new Model();
    sphereModel->_meshes.push_back(*sphereMesh);
    GameObject sphereObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereModel, 0, glm::vec3(0, 0, 0));
    objects->push_back(sphereObject);

    //TREE
    std::string pathModelTree = modelsPath + "/green_pine.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *tree, 0, glm::vec3(0, 0, 0));
    objects->push_back(treeObject);

    //TRUNK
    auto* trunk = new Model(modelsPath + "/trunk.obj");
    GameObject trunkObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *trunk, 0, glm::vec3(0, 0, 0));
    objects->push_back(trunkObject);

    //RUNE
    Model* rune = new Model(modelsPath + "/runejeanne.obj");
    GameObject runeObject(glm::vec3(-30.f,0.f,-5.f), 6.f, glm::vec3(90.f, 0.f, 0.f), *rune, 0, glm::vec3(0, 0, 0));
    objects->push_back(runeObject);

    //HUT
    Model* hut = new Model(modelsPath + "/Hut.obj");
    GameObject hutObject(glm::vec3(-10.f,-12.f,-5.f), 4.f, glm::vec3(0.f, 45.f, 0.f), *hut, 0, glm::vec3(0, 0, 0));
    objects->push_back(hutObject);

    //TERRAIN
    Model* terrain = new Model(modelsPath + "/terrain.obj");
    GameObject terrainObject(glm::vec3(0.f,-70.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *terrain, 0, glm::vec3(0, 0, 0));
    objects->push_back(terrainObject);


    _objects = *objects;
}
