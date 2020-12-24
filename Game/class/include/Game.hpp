#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"

class Game {
private:
    int _score = 0;
    Camera _camera;
    MapManager *_map;
public:
    //CONSTRUCTOR
    inline Game():_map(new MapManager()), _camera(){};

    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline const int score() {return _score;}
    void update();
    inline void Delete(){ _map->Delete(); };
};


#endif //IMACDREAM_GAME_HPP
