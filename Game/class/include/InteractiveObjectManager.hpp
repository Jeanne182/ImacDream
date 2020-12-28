#ifndef IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
#define IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP

#include "./GameObject.hpp"
#include "./InteractiveObject.hpp"
#include <vector>

enum ObjectsInteractive{

};

class InteractiveObjectManager {
private:
//    std::vector<InteractiveObject> _objectsToFind;

public:
    std::vector<InteractiveObject> _objectsToFind;//PRIVATE
    inline InteractiveObjectManager(){ InteractiveObjectsManager();};
    inline InteractiveObjectManager(std::vector<InteractiveObject> &objectsToFind):_objectsToFind(objectsToFind){};
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void InteractiveObjectsManager();

    //GETTERS

};



#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
