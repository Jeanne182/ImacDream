#include "./../include/Camera.hpp"
#include <cmath>
#include "glimac/FreeflyCamera.hpp"
#include <iostream>

void Camera::computeDirectionVectors(){
    this->m_FrontVector = glm::vec3(glm::cos(this->m_fTheta)*glm::sin(this->m_fPhi),
                                    glm::sin(this->m_fTheta),
                                    glm::cos(this->m_fTheta)*glm::cos(this->m_fPhi)) ;
    this->m_LeftVector = glm::vec3(glm::sin(this->m_fPhi + M_PI/2), 0, glm::cos(this->m_fTheta + M_PI/2));
    this->m_UpVector = glm::cross(this->m_FrontVector , this->m_LeftVector);
}

void Camera::moveLeft(float t){
    this->m_Position += t * this->m_LeftVector;
    computeDirectionVectors();
}

void Camera::moveFront(float t){
    this->m_Position += t * this->m_FrontVector;
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

void Camera::event(const SDL_Event &e) {
    switch(e.type)
    {
        case SDL_MOUSEBUTTONUP :
            if(e.button.button == SDL_BUTTON_WHEELUP){
                moveFront(0.5f);
            }
            else if(e.button.button == SDL_BUTTON_WHEELDOWN){
                moveFront(-0.5f);
            }
            break;
//        case SDL_MOUSEBUTTONDOWN:
//            OriginX = e.button.x - WINDOW_WIDTH/2;
//            OriginY = e.button.y - WINDOW_HEIGHT/2;

            /* Touche clavier */
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_z)
            {
                KEY_UP_PRESSED = true;

            }
            if (e.key.keysym.sym==SDLK_s)
            {
                KEY_DOWN_PRESSED = true;
            }
            if (e.key.keysym.sym==SDLK_q)
            {
                KEY_LEFT_PRESSED = true;
            }
            if (e.key.keysym.sym==SDLK_d)
            {
                KEY_RIGHT_PRESSED = true;
            }
            break;

        case SDL_KEYUP:
            if (e.key.keysym.sym==SDLK_z)
            {
                KEY_UP_PRESSED = false;
            }
            if (e.key.keysym.sym==SDLK_s)
            {
                KEY_DOWN_PRESSED = false;
            }
            if (e.key.keysym.sym==SDLK_q)
            {
                KEY_LEFT_PRESSED = false;
            }
            if (e.key.keysym.sym==SDLK_d)
            {
                KEY_RIGHT_PRESSED = false;
            }
            break;

        default:
            break;
    }

//    if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
//        float x = windowManager.getMousePosition().x - WINDOW_WIDTH/2;
//        std::cout<<"x Position =  "<<x<<std::endl;
//        std::cout<<"Origin =  "<<OriginX <<" , "<<OriginY<<std::endl;
//        std::cout<<"Distance =  "<<x - OriginX<<std::endl<<std::endl;
//
//        rotateLeft((OriginX - x)*0.01);
//        if(xOld >= x){
//            OriginX = x;
//        }
//        xOld = x;
//        float y = windowManager.getMousePosition().y - WINDOW_HEIGHT/2;
//        rotateUp((-y + OriginY)*0.01);
//        if(yOld >= y){
//            OriginY = y;
//        }
//        yOld = y;
//    }
}

void Camera::update() {
    float speed = 1.f;

    if (KEY_UP_PRESSED)
    {
        moveFront(speed);
    }
    if (KEY_DOWN_PRESSED)
    {
        moveFront(-speed);
    }
    if (KEY_LEFT_PRESSED)
    {
        moveLeft(speed);
    }
    if (KEY_RIGHT_PRESSED)
    {
        moveLeft(-speed);
    }
}
