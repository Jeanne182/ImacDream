#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"
#include "./Light.hpp"

class Game {
private:
    int _score = 0;
    MapManager *_map;
    Light _pointLight;
public:
    Camera _camera;// PRIVATE
    //CONSTRUCTOR
    inline Game():_map(new MapManager()), _camera(), _pointLight(_camera.getViewMatrix()){};

    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline const int score() {return _score;}
    void update();
    inline void Delete(){ _map->Delete(); };
};


#endif //IMACDREAM_GAME_HPP
