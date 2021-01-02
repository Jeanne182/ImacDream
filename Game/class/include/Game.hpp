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
    inline Game():_map(new MapManager()), _camera(), _pointLight(_camera.getViewMatrix()), _sky(), _score(0){ };
    inline Game():_map(new MapManager()), _pointLight(),  _camera(), _sky(){ };
    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline const int score() {return _score;};
    inline void increaseScore() { _score++ ;};
    void update();
    inline void Delete(){ _map->Delete(); delete _map; _sky.deleteBuffers(); };
};


#endif //IMACDREAM_GAME_HPP
