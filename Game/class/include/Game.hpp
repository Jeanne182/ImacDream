#ifndef IMACDREAM_GAME_HPP
#define IMACDREAM_GAME_HPP

#include "./Camera.hpp"
#include "./MapManager.hpp"

class Game {
private:
    int _score = 0;
    Camera _camera;
    MapManager _mapManager;
public:
    inline Game(const FilePath &applicationPath):_mapManager(applicationPath){auto* camera = new Camera(); _camera = *camera; };
    void display(glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location);
    void event(const SDL_Event &e);
    inline const int score() {return _score;}
    void update();
};


#endif //IMACDREAM_GAME_HPP
