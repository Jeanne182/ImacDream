#ifndef IMACDREAM_WATER_HPP
#define IMACDREAM_WATER_HPP

#include "./GameObject.hpp"

class Water : public GameObject {
private:
    float _waveTime = 0.f;
    float _waveSpeed = 1.f;
public:
    Water();
    ~Water(){};
    void displayWater();
    void useMatrix();
    void updateTime();
};

#endif //IMACDREAM_WATER_HPP
