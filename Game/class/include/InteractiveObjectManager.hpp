#ifndef IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
#define IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP

#include "./GameObject.hpp"
#include "./InteractiveObject.hpp"
#include <vector>

enum ObjectsInteractive{

};

class InteractiveObjectManager {
private:
    std::vector<InteractiveObject> _objectsToFind;

public:
    inline InteractiveObjectManager(){ InteractiveObjectsManager();};
    inline InteractiveObjectManager(std::vector<InteractiveObject> &objectsToFind):_objectsToFind(objectsToFind){};
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void InteractiveObjectsManager();

    //GETTERS
    inline std::vector<InteractiveObject> getObjects(){ return _objectsToFind ;};

};



#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
