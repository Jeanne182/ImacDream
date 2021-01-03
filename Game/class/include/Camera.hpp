#ifndef IMACDREAM_CAMERA_HPP
#define IMACDREAM_CAMERA_HPP

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <map>

class Camera {
private :
    glm::vec3 m_Position;
    float m_fPhi, m_fTheta;
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
    float _xOld = 0.f;
    float _yOld = 0.f;
    void computeDirectionVectors();
    std::map<std::string, glm::vec3> _futuresPositions;

    bool KEY_UP_PRESSED = false;
    bool KEY_DOWN_PRESSED = false;
    bool KEY_LEFT_PRESSED = false;
    bool KEY_RIGHT_PRESSED = false;

public:
    //glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;//RPIVATE
    Camera():
            m_Position(glm::vec3(0.,0.,0.)), m_fPhi(M_PI), m_fTheta(0.),
            _futuresPositions{std::make_pair("UP", glm::vec3(0., 0., 0.)), std::make_pair("DOWN", glm::vec3(0., 0., 0.)), std::make_pair("LEFT", glm::vec3(0., 0., 0.)), std::make_pair("RIGHT", glm::vec3(0., 0., 0.))}
    {
        computeDirectionVectors();
    }
    ~Camera()=default;

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
    inline glm::vec3 getPosition() const { return m_Position;};
    inline glm::vec3 getFrontVector() const { return m_FrontVector;};
    inline glm::vec3 getLeftVector() const { return m_LeftVector;};
    inline glm::vec3 getUpVector() const { return m_UpVector;};
    inline std::map<std::string, glm::vec3> getFuturesPositions() const { return _futuresPositions;};


    inline void setPositionY(const float &y) { m_Position.y = y;};
    void event(const SDL_Event &e, std::map<const std::string, bool> &movePossible);
    void update(std::map<const std::string, bool> &movePossible);
    void setFuturesPositions(const float t);
};

#endif //IMACDREAM_CAMERA_HPP