#include "../include/InteractiveObjectManager.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>
#include <map>
#include "../include/Utils.hpp"


void InteractiveObjectManager::display(const glm::mat4 &cameraView) {

    //InteractiveObject *dragonegg1 = _objectsToFind.find(0)->second;

    _objectsToFind.setPosition(glm::vec3(3.f, -10.f, -8.f));
    _objectsToFind.setCenter();
    //std::cout << "center : " << _objectsToFind.getCenter() << std::endl;
    _objectsToFind.setHitboxRadius();
    _eggs[0].first = _objectsToFind.getCenter();
    _eggs[0].second = _objectsToFind.getHitboxRadius();
    _objectsToFind.update(cameraView);

    _objectsToFind.setPosition(glm::vec3(5.f, -10.f, -8.f));
    _objectsToFind.setCenter();
    //std::cout << "center : " << _objectsToFind.getCenter() << std::endl;
    _objectsToFind.setHitboxRadius();
    _eggs[1].first = _objectsToFind.getCenter();
    _eggs[1].second = _objectsToFind.getHitboxRadius();
    _objectsToFind.update(cameraView);


}

void InteractiveObjectManager::deleteBuffers() {


}

InteractiveObjectManager::InteractiveObjectManager():_objectsToFind(),_nbObjects(8), _exist(), _eggs(){
    //auto* InteractiveObjects = new std::map<int, InteractiveObject*>;

    for(int i=0; i<_nbObjects ; i++){
        _exist.push_back(true);
    }


    //DRAGON EGG
    auto* egg = new Model(AssetManager::Get()->modelFile("dragon_egg.obj"));
    GameObject eggObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *egg, 0, glm::vec3(0, 0, 0));
    //InteractiveObjects->insert(std::make_pair(eggObject.getID(), &eggObject));


    _objectsToFind = eggObject;
}

int InteractiveObjectManager::selectedEgg(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition){
    for(unsigned int i=0; i<_nbObjects; i++){
        if(isSelected(cameraView, cameraPosition, _eggs[i].first, _eggs[i].second)){
            return i;
        }
    }
    return -1;
}


// test if the camera is pointing on an object

bool isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition, const glm::vec3 centerObj, const float radiusObj) {


    // Distance between the camera and the center of the interactive object
    glm::vec3 distanceVector = glm::vec3(cameraView*glm::vec4(centerObj, 1.)) ;
    std::cout << "cameraPosition : " << cameraPosition << std::endl;
    std::cout << "distanceVector : " << distanceVector << std::endl;

    glm::vec3 directionVectorCam = glm::vec3(glm::vec4(0, 0, -1, 0));

    std::cout << "directionVectorCam : " <<directionVectorCam << std::endl;

    // Find the direction vector of the camera ray
    //glm::vec3 directionVectorCam = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z-1.) - cameraPosition ;

    // Distance between the camera and the center of the interactive object projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;
    std::cout << "distanceToCenter : " << distanceToCenter << std::endl;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0){
        return false;
    }

    // Find the closest distance between the center of the object on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));
    std::cout << "hitbox radius : " << radiusObj << std::endl;
    std::cout << "distanceToRay : " << distanceToRay << std::endl;

    // Check if the ray intersect the sphere or not depending on the radius
    if(distanceToRay > radiusObj){
        return false ;
    }

    return true;

}





