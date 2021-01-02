#ifndef IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
#define IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP

#include "./GameObject.hpp"
#include <vector>

enum ObjectsInteractive{

};

class InteractiveObjectManager {
private:
    GameObject _objectsToFind;
    std::vector<bool> _exist;
    int _nbObjects;
    std::vector<std::pair<glm::vec3, float>> _eggs;//centers, hitboxRadius
    std::vector<std::pair<glm::vec3, float>> _positions;//position, scale



public:
    InteractiveObjectManager();
    inline InteractiveObjectManager(GameObject &objectsToFind):_objectsToFind(objectsToFind){};
    void deleteBuffers();


    //SETTERS
    void setBoolValue(const int id);
    void setHitboxRadius(const int id);
    void setCenter(const int id);

    //GETTERS
    inline GameObject getObjects(){ return _objectsToFind ;};
    inline std::vector<bool> getExist(){ return _exist ;};

    //METHODS
    void display(const glm::mat4 &cameraView);
    int selectedEgg(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition);
    glm::vec3 findMax(const int id);
    glm::vec3 findMin(const int id);
    bool isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition, const int i);


};



#endif //IMACDREAM_INTERACTIVEOBJECTMANAGER_HPP
