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
    int _scoreMax = 2;
    MapManager *_map;
    Light _pointLight;
    Camera _camera;
    Skybox _sky;
    Music _soundCollect;
    std::map<const std::string, bool> _move;

public:
    //CONSTRUCTOR
    inline Game():_score(0), _map(new MapManager()),  _pointLight(), _camera(), _sky(), _soundCollect("collect"),
    _move{std::make_pair("UP", true), std::make_pair("DOWN", true), std::make_pair("LEFT", true), std::make_pair("RIGHT", true)}{};
    ~Game()=default;

    //METHODS
    void display();
    void event(const SDL_Event &e);
    inline void increaseScore() { _soundCollect.play(0); _score++ ;};
    inline void setScore(const int score) { _score=score ;};
    void update();
    void collisionsManager(const float t);
    void checkCollisionsObj(const int nbObj, const std::vector<std::pair<glm::vec3, float>> CenterRadius);
    void checkCollisionsMap();
    inline void Delete(){ _map->Delete(); delete _map; _sky.deleteBuffers(); _soundCollect.Delete();};
    void ResetMove();
    void ResetGame();

    //GETTERS
    inline int getScore() {return _score;};
    inline bool lightOn() {return _pointLight.getLightOn();}
    inline MapManager* getMap(){ return _map;};
    inline Camera getCamera(){ return _camera;};
    inline Light light() { return _pointLight; }
    inline int scoreMax() { return _scoreMax; }
};


#endif //IMACDREAM_GAME_HPP
