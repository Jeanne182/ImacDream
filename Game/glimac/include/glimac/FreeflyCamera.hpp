#pragma once
#include <cmath>
#include <glimac/glm.hpp>

class FreeflyCamera {
private :
  glm::vec3 m_Position;
  float m_fPhi, m_fTheta;
  glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
  void computeDirectionVectors();

public:
    FreeflyCamera():
    m_Position(glm::vec3(0., 0., 0.)), m_fPhi(M_PI), m_fTheta(0.){
      computeDirectionVectors();
    }

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
};
