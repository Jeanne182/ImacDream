#include<cmath>
#include "glimac/FreeflyCamera.hpp"
#include<iostream>
void FreeflyCamera::computeDirectionVectors(){
  this->m_FrontVector = glm::vec3(glm::cos(this->m_fTheta)*glm::sin(this->m_fPhi),
                                  glm::sin(this->m_fTheta),
                                  glm::cos(this->m_fTheta)*glm::cos(this->m_fPhi)) ;
  this->m_LeftVector = glm::vec3(glm::sin(this->m_fPhi + M_PI/2), 0, glm::cos(this->m_fTheta + M_PI/2));
  this->m_UpVector = glm::cross(this->m_FrontVector , this->m_LeftVector);
}

void FreeflyCamera::moveLeft(float t){
  this->m_Position += t * this->m_LeftVector;
  computeDirectionVectors();
}

void FreeflyCamera::moveFront(float t){
  this->m_Position += t * this->m_FrontVector;
  computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees){
  this->m_fPhi += glm::radians(degrees);
  computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees){
  this->m_fTheta += glm::radians(degrees);
  computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const{
  glm::vec3 point = this->m_Position + this->m_FrontVector;
  return glm::lookAt(this->m_Position, point, this->m_UpVector); //eye, point, up

}
