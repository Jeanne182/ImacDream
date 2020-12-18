#ifndef IMACDREAM_CAMERA_HPP
#define IMACDREAM_CAMERA_HPP

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>


class Camera {
private :
    glm::vec3 m_Position;
    float m_fPhi, m_fTheta;
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
    void computeDirectionVectors();

    bool KEY_UP_PRESSED = false;
    bool KEY_DOWN_PRESSED = false;
    bool KEY_LEFT_PRESSED = false;
    bool KEY_RIGHT_PRESSED = false;

public:
    Camera():
            m_Position(glm::vec3(0., 0., 0.)), m_fPhi(M_PI), m_fTheta(0.){
        computeDirectionVectors();
    }

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;

    void event(const SDL_Event &e);
    void update();
};

#endif //IMACDREAM_CAMERA_HPP