#ifndef IMACDREAM_WATER_HPP
#define IMACDREAM_WATER_HPP

#include "./GameObject.hpp"

class Water : public GameObject {
private:
    static constexpr float _waveSpeed = 1.f;
public:
    Water();
    ~Water()=default;
    void display();
    void useMatrix();
};

#endif //IMACDREAM_WATER_HPP
