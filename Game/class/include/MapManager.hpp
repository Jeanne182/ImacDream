#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include <glimac/SDLWindowManager.hpp>
#include "./Terrain.hpp"
#include "./Camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <map>
#include<tuple>
#include "./Water.hpp"



class MapManager {
private:
    Terrain _terrain;
    Water _water;
public:

    inline MapManager():_terrain(), _water(){}
    ~MapManager()=default;
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _water.deleteBuffers();};


    void event(const SDL_Event &e,const glm::mat4 &cameraView, const glm::vec3 &cameraPosition);

    //SETTERS

};

#endif //IMACDREAM_MAPMANAGER_HPP
