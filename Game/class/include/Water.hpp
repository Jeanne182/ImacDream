#ifndef IMACDREAM_WATER_HPP
#define IMACDREAM_WATER_HPP

#include "./GameObject.hpp"

class Water : public GameObject {
public:
    Water();
    ~Water(){};
    void displayWater();
};

#endif //IMACDREAM_WATER_HPP
