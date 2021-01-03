#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"
#include "./Light.hpp"
#include "./Skybox.hpp"
#include "./Music.hpp"
#include <map>


class Game {
private:
    int _score;
    MapManager *_map;
    Light _pointLight;
    Camera _camera;
    Skybox _sky;
    Music _soundCollect;
    std::map<const std::string, bool> _move;

public:
    //CONSTRUCTOR
    inline Game():_map(new MapManager()), _pointLight(),  _camera(), _sky(), _score(0), _soundCollect("collect"),
    _move{std::make_pair("UP", true), std::make_pair("DOWN", true), std::make_pair("LEFT", true), std::make_pair("RIGHT", true)}{};
    ~Game()=default;

    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline void increaseScore() { _soundCollect.play(0); _score++ ;};
    void update();
    void collisionsManager(const float t);
    void checkCollisions(const int nbObj, const std::vector<std::pair<glm::vec3, float>> CenterRadius);
    inline void Delete(){ _map->Delete(); delete _map; _sky.deleteBuffers(); _soundCollect.Delete();};
    void ResetMove();
    void ResetGame();

    //GETTERS
    inline const int getScore() {return _score;};
    inline bool lightOn() {return _pointLight.getLightOn();}
    inline MapManager* getMap(){ return _map;};
    inline Camera getCamera(){ return _camera;};
    inline Light light() { return _pointLight; }
};


#endif //IMACDREAM_GAME_HPP
