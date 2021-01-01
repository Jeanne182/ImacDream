#ifndef IMACDREAM_GAMEOBJECT_HPP
#define IMACDREAM_GAMEOBJECT_HPP
#include <glimac/common.hpp>
#include "./Model.hpp"
#include <glimac/SDLWindowManager.hpp>
#include "./Camera.hpp"

using namespace glimac;

class GameObject {
protected:
    glm::vec3 _position, _angles;
    float _scale;
    glm::mat4 _M, _MV, _MVP, _N;
    //Model *_model;
    float _hitboxRadius;
    glm::vec3 _center;
//    Model *_model; //PRIVATE

public :
    Model *_model;//PRIVATE

    //CONSTRUCTORS & DESCTRUCTOR
    GameObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Model &model, const float &hitboxRadius, const glm::vec3 &center);
    GameObject(const GameObject &object);
    virtual ~GameObject()=default;

    //GETTERS
    inline glm::vec3 getPosition(){ return _position; };
    inline float getScale(){ return _scale; };
    inline float getHitboxRadius(){ return _hitboxRadius; };
    inline glm::vec3 getCenter(){ return _center; };



    //SETTERS
    inline void setPosition(glm::vec3 position){ _position = position; }
    inline void setAngles(glm::vec3 angles){ _angles = angles; }
    inline void setScale(float scale){ _scale = scale; }
    inline void addPosition(glm::vec3 position){ _position += position; }
    inline void addAngles(glm::vec3 angles){ _angles += angles; }
    inline void addScale(float scale){ _scale += scale; }
    void setHitboxRadius();
    void setCenter();


    virtual //METHODS
    void display(); //OK
    void setMatrix(); //OK
    void computeMatrix(const glm::mat4 &cameraView); //OK
    void useMatrix() const; //OK
    void update(const glm::mat4 &cameraView);
    void deleteBuffers();
    glm::vec3 findMax();
    glm::vec3 findMin();
    int numberVertices();



};

#endif //IMACDREAM_GAMEOBJECT_HPP
