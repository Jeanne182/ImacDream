#include "../include/InteractiveObjectManager.hpp"
#include "../include/AssetsManager.hpp"
#include <map>
#include "../include/Utils.hpp"


void InteractiveObjectManager::display(const glm::mat4 &cameraView) {

    if(_exist[0]==true){
        _objectsToFind.setPosition(_positions[0].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[1]==true){
        _objectsToFind.setPosition(_positions[1].first);
        //_objectsToFind.setCenter();
        //_objectsToFind.setHitboxRadius();
        //_eggs.push_back(std::make_pair(_objectsToFind.getCenter(), _objectsToFind.getHitboxRadius()));
        _objectsToFind.update(cameraView);
    }
    if(_exist[2]==true){
        _objectsToFind.setPosition(_positions[2].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[3]==true){
        _objectsToFind.setPosition(_positions[3].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[4]==true){
        _objectsToFind.setPosition(_positions[4].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[5]==true){
        _objectsToFind.setPosition(_positions[5].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[6]==true){
        _objectsToFind.setPosition(_positions[6].first);
        _objectsToFind.update(cameraView);
    }
    if(_exist[7]==true){
        _objectsToFind.setPosition(_positions[7].first);
        _objectsToFind.update(cameraView);
    }



}

void InteractiveObjectManager::deleteBuffers() {
    _objectsToFind.deleteBuffers();

}

InteractiveObjectManager::InteractiveObjectManager():_objectsToFind(),_nbObjects(8), _exist(), _eggs(), _positions(){


    //DRAGON EGG
    auto* egg = new Model(AssetManager::Get()->modelFile("dragon_egg.obj"));
    GameObject eggObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *egg, 0, glm::vec3(0, 0, 0));

    _objectsToFind = eggObject;


    for(int i=0; i<_nbObjects ; i++){
        _exist.push_back(true);
        _positions.push_back(std::make_pair(glm::vec3(i*5.f, 2.f, 0.f), 1.f));
        _eggs.push_back(std::make_pair(glm::vec3(0., 0., 0.), 0.f));
        setCenter(i);
        setHitboxRadius(i);

    }




}

int InteractiveObjectManager::selectedEgg(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition){
    for(unsigned int i=0; i<_nbObjects; i++){
        if(_exist[i]==true){
            if(isSelected(cameraView, cameraPosition, i)){
                return i;
            }
        }
    }
    return -1;
}


// test if the camera is pointing on an object
bool InteractiveObjectManager::isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition, const int i) {


    // Distance between the camera and the center of the interactive object
    glm::vec3 distanceVector = glm::vec3(cameraView*glm::vec4(_eggs[i].first, 1.)) ;
    std::cout << std::endl<< std::endl<< "cameraPosition : " << cameraPosition << std::endl;
    std::cout << "Center : " << _eggs[i].first << std::endl;
    std::cout << "distanceVector : " << distanceVector << std::endl;
    // Find the direction vector of the camera ray

    glm::vec3 directionVectorCam = glm::vec3(glm::vec4(0, 0, -1, 0));


    // Distance between the camera and the center of the interactive object projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;
    std::cout << "distanceToCenter : " << distanceToCenter << std::endl;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0){
        return false;
    }

    // Find the closest distance between the center of the object on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));
    std::cout << "hitbox radius : " << _eggs[i].second << std::endl;
    std::cout << "distanceToRay : " << distanceToRay << std::endl;

    // Check if the ray intersect the sphere or not depending on the radius
    if(distanceToRay > _eggs[i].second){
        return false ;
    }

    return true;

}


void InteractiveObjectManager::setBoolValue(const int id){
    _exist.at(id)=false;
}


void InteractiveObjectManager::setCenter(const int id){
    glm::vec3 max = findMax(id);
    glm::vec3 min = findMin(id);
    _eggs.at(id).first=((max+min)/glm::vec3(2., 2., 2.));
    std::cout << "center  " << id << "  :  " <<  _eggs.at(id).first<<std::endl;

}



void InteractiveObjectManager::setHitboxRadius(const int id){
    float radius ;
    for(auto meshes : _objectsToFind.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position*_positions[id].second+_positions[id].first);
            radius = float(glm::distance(vertex, _eggs[id].first));
            if(radius > _eggs[id].second ) {
                _eggs[id].second = radius;
            }
        }
    }
}



glm::vec3 InteractiveObjectManager::findMax(const int id){
    glm::vec3 max = _positions[id].first;
    for(auto meshes : _objectsToFind.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position * _positions[id].second + _positions[id].first);
            if(vertex.x> max.x) max.x = vertex.x;
            if(vertex.y > max.y) max.y = vertex.y;
            if(vertex.z > max.z) max.z = vertex.z;
        }
    }
    return max;
}

glm::vec3 InteractiveObjectManager::findMin(const int id){
    glm::vec3 min =  _positions[id].first;
    for(auto meshes : _objectsToFind.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position* _positions[id].second+ _positions[id].first);
            if(vertex.x< min.x) min.x = vertex.x;
            if(vertex.y < min.y) min.y = vertex.y;
            if(vertex.z < min.z) min.z = vertex.z;
        }
    }
    return min;
}



