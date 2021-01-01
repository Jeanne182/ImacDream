#ifndef IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
#define IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP

#include "./GameObject.hpp"
#include "./InteractiveObject.hpp"
#include <map>

enum ObjectsInteractive{

};

class InteractiveObjectManager {
private:
    GameObject _objectsToFind;
    std::vector<bool> _exist;
    int _nbObjects;
    std::vector<std::pair<glm::vec3, float>> _eggs;



public:
    InteractiveObjectManager();
    inline InteractiveObjectManager(InteractiveObject &objectsToFind):_objectsToFind(objectsToFind){};
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    int selectedEgg(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition);


        //GETTERS
    inline GameObject getObjects(){ return _objectsToFind ;};

};

bool isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition,const glm::vec3 centerObj, const float radiusObj);


#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
