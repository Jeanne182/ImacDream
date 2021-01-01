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
    int nbObjects=8;



public:
    InteractiveObjectManager();
    inline InteractiveObjectManager(InteractiveObject &objectsToFind):_objectsToFind(objectsToFind){};
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();

    //GETTERS
    inline GameObject getObjects(){ return _objectsToFind ;};

};



#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
