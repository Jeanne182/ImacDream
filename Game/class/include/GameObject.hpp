#ifndef IMACDREAM_GAMEOBJECT_HPP
#define IMACDREAM_GAMEOBJECT_HPP
#include <glimac/common.hpp>
#include "./Mesh.hpp"
#include "./Model.hpp"

using namespace glimac;

class GameObject {
protected:
    glm::vec3 _position, _angles;
    float _scale;
    glm::mat4 _M, _MV, _MVP, _N;
    Mesh *_mesh;

public :
    //CONSTRUCTORS
    GameObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Mesh &mesh);
    GameObject(const GameObject &object);

    //GETTERS
    inline glm::vec3 getPosition(){ return _position; };

    //SETTERS
    inline void setPosition(glm::vec3 position){ _position = position; }
    inline void setAngles(glm::vec3 angles){ _angles = angles; }
    inline void setScale(float scale){ _scale = scale; }

    inline void addPosition(glm::vec3 position){ _position += position; }
    inline void addAngles(glm::vec3 angles){ _angles += angles; }
    inline void addScale(float scale){ _scale += scale; }

    //METHODS
    void display(Program &program);
    void setMatrix();
    void computeMatrix(const glm::mat4 &cameraView);
    void useMatrix() const;
    void update(const glm::mat4 &cameraView);
    void deleteBuffers();

};

#endif //IMACDREAM_GAMEOBJECT_HPP