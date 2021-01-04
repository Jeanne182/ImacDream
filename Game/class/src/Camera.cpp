#include "./../include/Camera.hpp"
#include "glimac/FreeflyCamera.hpp"
#include <iostream>

void Camera::computeDirectionVectors(){
    this->m_FrontVector = glm::vec3(glm::cos(this->m_fTheta)*glm::sin(this->m_fPhi),
                                    glm::sin(this->m_fTheta),
                                    glm::cos(this->m_fTheta)*glm::cos(this->m_fPhi)) ;
    this->m_LeftVector = glm::vec3(glm::cos(this->m_fPhi), 0, - glm::sin(this->m_fPhi));
    this->m_UpVector = glm::cross(this->m_FrontVector , this->m_LeftVector);
}

void Camera::moveLeft(float t){
    this->m_Position[0] += t * this->m_LeftVector[0];
    this->m_Position[2] += t * this->m_LeftVector[2];
    computeDirectionVectors();
}

void Camera::moveFront(float t){
    this->m_Position[0] += t * this->m_FrontVector[0];
    this->m_Position[2] += t * this->m_FrontVector[2];
    computeDirectionVectors();
}

void Camera::rotateLeft(float degrees){
    this->m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void Camera::rotateUp(float degrees){
    this->m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const{
    glm::vec3 point = this->m_Position + this->m_FrontVector;
    return glm::lookAt(this->m_Position, point, this->m_UpVector); //eye, point, up
}

void Camera::event(const SDL_Event &e, std::map<const std::string, bool> &movePossible) {
    float speed_mouse = 1.5f;
    float speed_scroll = 10.f;
    float xDelta, yDelta;

    switch(e.type)
    {
        case SDL_MOUSEWHEEL :
            if(e.wheel.y> 0 && movePossible["UP"]) moveFront(speed_scroll); // scroll up
            else if(e.wheel.y < 0 && movePossible["DOWN"]) moveFront(-speed_scroll); // scroll down
            break;

        case SDL_MOUSEMOTION:

            ////USE THESE TWO LINES TO PLAY ON A VIRTUAL MACHINE
//            xDelta = e.motion.xrel - _xOld;
//            yDelta = e.motion.yrel - _yOld;

            /////USE THESE TWO LINES TO PLAY ON ANOTHER DEVICE
            xDelta = e.motion.xrel;
            yDelta = e.motion.yrel;

            _xOld =  e.motion.xrel;
            _yOld =  e.motion.yrel;

            if(m_fTheta  + glm::radians(- yDelta * speed_mouse)  > -5) m_fTheta = -5;
            else if(m_fTheta + glm::radians(- yDelta * speed_mouse)  < -7.5) m_fTheta = -7.5;
            else rotateUp(- yDelta * speed_mouse);
            rotateLeft(- xDelta * speed_mouse);
            break;

        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_z || e.key.keysym.sym==SDLK_UP) KEY_UP_PRESSED = true;
            if (e.key.keysym.sym==SDLK_s || e.key.keysym.sym==SDLK_DOWN) KEY_DOWN_PRESSED = true;
            if (e.key.keysym.sym==SDLK_q || e.key.keysym.sym==SDLK_LEFT) KEY_LEFT_PRESSED = true;
            if (e.key.keysym.sym==SDLK_d || e.key.keysym.sym==SDLK_RIGHT) KEY_RIGHT_PRESSED = true;
            break;

        case SDL_KEYUP:
            if (e.key.keysym.sym==SDLK_z || e.key.keysym.sym==SDLK_UP) KEY_UP_PRESSED = false;
            if (e.key.keysym.sym==SDLK_s || e.key.keysym.sym==SDLK_DOWN) KEY_DOWN_PRESSED = false;
            if (e.key.keysym.sym==SDLK_q || e.key.keysym.sym==SDLK_LEFT) KEY_LEFT_PRESSED = false;
            if (e.key.keysym.sym==SDLK_d || e.key.keysym.sym==SDLK_RIGHT) KEY_RIGHT_PRESSED = false;
            break;

        default:
            break;
    }
}

void Camera::update(std::map<const std::string, bool> &movePossible) {
    float speed = 1.5f;
    if (KEY_UP_PRESSED && movePossible["UP"]) moveFront(speed);
    if (KEY_DOWN_PRESSED && movePossible["DOWN"]) moveFront(-speed);
    if (KEY_LEFT_PRESSED && movePossible["LEFT"])  moveLeft(speed);
    if (KEY_RIGHT_PRESSED && movePossible["RIGHT"]) moveLeft(-speed);
}

void Camera::setFuturesPositions(const float t) {
    _futuresPositions["UP"]=glm::vec3(m_Position[0]+t*m_FrontVector[0], 0., m_Position[2]+t*m_FrontVector[2]);
    _futuresPositions["DOWN"]=glm::vec3(m_Position[0]-t*m_FrontVector[0], 0., m_Position[2]-t*m_FrontVector[2]);
    _futuresPositions["LEFT"]=glm::vec3(m_Position[0]+t*m_LeftVector[0], 0., m_Position[2]+t*m_LeftVector[2]);
    _futuresPositions["RIGHT"]=glm::vec3(m_Position[0]-t*m_LeftVector[0], 0., m_Position[2]-t*m_LeftVector[2]);
}