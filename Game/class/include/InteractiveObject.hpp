#ifndef IMACDREAM_INTERACTIVEOBJECT_HPP
#define IMACDREAM_INTERACTIVEOBJECT_HPP

#include <vector>
#include "./../include/Camera.hpp"
#include "./../include/GameObject.hpp"
#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>


class InteractiveObject : public GameObject {
protected:
    int _value;
    //std::vector<InteractiveObject> _objectsToFind;


public :
    //CONSTRUCTORS
    inline InteractiveObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Mesh &mesh, const int &value): GameObject(position, scale, angles, mesh), _value(value){}

    //GETTERS
    inline int getValue(){ return _value; };

    //SETTERS
    inline void setValue(int value){ _value = value; }

    //METHODS
    //bool testCollision(GameObject object, double hitboxRadius, glm::vec3 mouseRayFront, glm::vec3 mouseRayBack);
    //bool isSelected(const SDL_Event &e, Camera &camera, glm::mat4 &ProjMatrix);


};

//std::vector<InteractiveObject>* InterractiveObjectsManager(const FilePath &applicationPath)()


#endif //IMACDREAM_INTERACTIVEOBJECT_HPP
