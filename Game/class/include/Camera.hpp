#ifndef IMACDREAM_CAMERA_HPP
#define IMACDREAM_CAMERA_HPP

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <map>
#include <vector>//TO DELETE

class Camera {
private :
    glm::vec3 m_Position;
    float m_fPhi, m_fTheta;
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
    float _xOld = 0.f;
    float _yOld = 0.f;

    int _i = 2; //TO DELETE
    std::vector<glm::vec3> _vector; //TO DELETE


    void computeDirectionVectors();
    std::map<std::string, glm::vec3> _futuresPositions;

    bool KEY_UP_PRESSED = false;
    bool KEY_DOWN_PRESSED = false;
    bool KEY_LEFT_PRESSED = false;
    bool KEY_RIGHT_PRESSED = false;

public:
    //glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;//RPIVATE
    Camera():
            m_Position(glm::vec3(0.f, 2.f, 0.f)), m_fPhi(M_PI), m_fTheta(0.),
            _futuresPositions{std::make_pair("UP", glm::vec3(0., 0., 0.)), std::make_pair("DOWN", glm::vec3(0., 0., 0.)), std::make_pair("LEFT", glm::vec3(0., 0., 0.)), std::make_pair("RIGHT", glm::vec3(0., 0., 0.))}
    {
        _vector = {glm::vec3(0,-0.2,0), glm::vec3(-1,0,1), glm::vec3(293.967,-1,-384.882), glm::vec3(141.253,0,-299.407),
                   glm::vec3(101.643,0,-47.177), glm::vec3(181.422,0,322.057), glm::vec3(279.425,0,-162.389), glm::vec3(12.149,0,-295.055),
                   glm::vec3(-216.376,0,183.185), glm::vec3(-437.107,0,368.451), glm::vec3(-275.794,0,-451.495), glm::vec3(47.953,0,-274.169),
                   glm::vec3(-190.991,0,-61.355), glm::vec3(-446.45,0,13.658), glm::vec3(-127.644,0,-482.366), glm::vec3(-470.803,0,-319.657),
                   glm::vec3(0.072,0,208.485), glm::vec3(491.218,0,215.118), glm::vec3(290.157,0,-95.479), glm::vec3(-269.462,0,302.001),
                   glm::vec3(-279.86,0,151.289), glm::vec3(153.646,0,392.346), glm::vec3(198.261,0,327.97), glm::vec3(171.311,0,169.106),
                   glm::vec3(-239.459,0,223.167), glm::vec3(1.859,0,411.852), glm::vec3(44.102,0,238.534), glm::vec3(-36.21,0,218.657),
                   glm::vec3(377.912,0,425.083), glm::vec3(-301.882,0,-431.267), glm::vec3(-311.922,0,261.539), glm::vec3(-339.667,0,-475.06),
                   glm::vec3(229.562,0,222.362), glm::vec3(-17.263,0,256.083), glm::vec3(-101.591,0,-139.948), glm::vec3(-285.004,0,-442.749),
                   glm::vec3(-460.953,0,-68.451), glm::vec3(490.354,0,-240.287), glm::vec3(25.046,0,373.536)};
        computeDirectionVectors();
    }
    ~Camera()=default;

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void event(const SDL_Event &e, std::map<const std::string, bool> &movePossible);
    void update(std::map<const std::string, bool> &movePossible);

    //GETTERS
    glm::mat4 getViewMatrix() const;
    inline glm::vec3 getPosition() const { return m_Position;};
    inline glm::vec3 getFrontVector() const { return m_FrontVector;};
    inline glm::vec3 getLeftVector() const { return m_LeftVector;};
    inline glm::vec3 getUpVector() const { return m_UpVector;};
    inline std::map<std::string, glm::vec3> getFuturesPositions() const { return _futuresPositions;};

    //SETTERS
    void setFuturesPositions(const float t);
    inline void setPosition(glm::vec3 position){ m_Position = position;};
};

#endif //IMACDREAM_CAMERA_HPP