#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"
#include "./Light.hpp"
#include "./Skybox.hpp"


class Game {
private:
    int _score;
    MapManager *_map;
    Light _pointLight;
    Camera _camera;
    Skybox _sky;

public:
    //CONSTRUCTOR
    inline Game():_map(new MapManager()), _pointLight(),  _camera(), _sky(), _score(0){ };
    ~Game()=default;
    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline void increaseScore() { _score++ ;};
    void update();
    inline void Delete(){ _map->Delete(); delete _map; _sky.deleteBuffers(); };



    //GETTER
    inline const int getScore() {return _score;};
    inline bool lightOn() {return _pointLight.getLightOn();}
    inline MapManager* getMap(){ return _map;};
    inline Camera getCamera(){ return _camera;};

};


#endif //IMACDREAM_GAME_HPP
