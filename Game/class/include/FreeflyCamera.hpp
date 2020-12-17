#pragma once

#include <glimac/glm.hpp>

class FreeflyCamera {
    

public:
FreeflyCamera():
    m_Position(glm::vec3(0.,0.,0.)), m_fPhi(glm::pi<float>()), m_fTheta(0.)
    {
        computeDirectionVectors();
    }
    inline void moveLeft(float t){m_Position += t*m_LeftVector;computeDirectionVectors();};
    inline void moveFront(float t){m_Position += t*m_FrontVector;computeDirectionVectors();};
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    //glm::mat4 getViewMatrix() const;
    inline glm::mat4 getViewMatrix() const{return glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);}

private:
    
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    void computeDirectionVectors();
};