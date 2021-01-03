#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"
#include "./Light.hpp"
#include "./Skybox.hpp"
#include "./Music.hpp"


class Game {
private:
    int _score;
    MapManager *_map;
    Light _pointLight;
    Camera _camera;
    Skybox _sky;
    Music _soundCollect;


public:
    //CONSTRUCTOR
    inline Game():_map(new MapManager()), _pointLight(),  _camera(), _sky(), _score(0), _soundCollect("collect"){ };
    ~Game()=default;
    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline void increaseScore() { _soundCollect.play(0); _score++ ;};
    void update();
    inline void Delete(){ _map->Delete(); delete _map; _sky.deleteBuffers(); _soundCollect.Delete();};
    //GETTER
    inline const int getScore() {return _score;};
    inline bool lightOn() {return _pointLight.getLightOn();}
    inline MapManager* getMap(){ return _map;};
    inline Camera getCamera(){ return _camera;};
    inline Light light() { return _pointLight; }
};


#endif //IMACDREAM_GAME_HPP
