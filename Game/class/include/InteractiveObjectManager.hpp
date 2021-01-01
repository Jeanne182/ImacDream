#ifndef IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
#define IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP

#include "./GameObject.hpp"
#include "./InteractiveObject.hpp"
#include <vector>

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
    void setBoolValue(const int id);


        //GETTERS
    inline GameObject getObjects(){ return _objectsToFind ;};
    inline std::vector<bool> getExist(){ return _exist ;};

};

bool isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition,const glm::vec3 centerObj, const float radiusObj);


#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
