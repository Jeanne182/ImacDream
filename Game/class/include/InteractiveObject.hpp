#ifndef IMACDREAM_INTERACTIVEOBJECT_HPP
#define IMACDREAM_INTERACTIVEOBJECT_HPP

#include <vector>
#include "./../include/Camera.hpp"
#include "./../include/GameObject.hpp"
#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>


class InteractiveObject : public GameObject {
protected:
    int _id;

public :
    //CONSTRUCTORS
    inline InteractiveObject(const glm::vec3 &position,
                             const float &scale,
                             const glm::vec3 &angles,
                             Model &model,
                             const float &hitboxRadius,
                             const glm::vec3 &center,
                             const int &value):
                             GameObject(position, scale, angles, model, hitboxRadius, center),
                             _value(value)
                             {}
    inline InteractiveObject(const InteractiveObject &interactiveObject): GameObject(interactiveObject), _value(interactiveObject._value){}

    //GETTERS
    inline int getID(){ return _id; };

    //SETTERS
    inline void setID(int id){ _id = id; }

    //METHODS
    bool isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition);


    };



#endif //IMACDREAM_INTERACTIVEOBJECT_HPP
