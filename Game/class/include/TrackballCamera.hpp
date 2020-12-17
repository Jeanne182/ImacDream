#pragma once

#include <glimac/glm.hpp>

class TrackballCamera {
    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    TrackballCamera():
        m_fDistance(5.), m_fAngleX(0.), m_fAngleY(0.) 
        {}

    inline void moveFront(float delta){if(delta>0){m_fDistance--;}else{m_fDistance++;}}
    
    inline void rotateLeft(float degrees){m_fAngleY += degrees;}
    
    inline void rotateUp(float degrees){m_fAngleX += degrees;}

    glm::mat4 getViewMatrix() const;
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
};