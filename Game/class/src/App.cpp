#include "../include/App.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"

#include <utility>

void App::event(const SDL_Event &e) {
    switch(_layout){
        case LAYOUT_MENU:
        _game.event(e);
            switch(e.type){
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym==SDLK_RETURN )
                    {
                        _layout = LAYOUT_GAME;
                    }
                    break;

            }
            break;

        case LAYOUT_GAME:
            _game.event(e);
            switch(e.type){
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym==SDLK_KP_PLUS ){
                        _game.increaseScore();
                        _texts.getText("eggs")->replace("Dragon eggs : " + std::to_string(_game.score()));
                    }

//                    if (e.key.keysym.sym==SDLK_a ){
//                        if (_game.lightOn()) _texts.getText("light")->replace("Light on");
//                        else _texts.getText("light")->replace("Light off");
//
//                    }
            }
            if(_game.score() == 3){
                _layout = LAYOUT_GAME_OVER;
            }


        case LAYOUT_GAME_OVER:
            switch(e.type){
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym==SDLK_RETURN) {
                        _layout = LAYOUT_MENU;
                    }
            }
    }

}

void App::draw() {
    switch(_layout){
        case LAYOUT_GAME:
            drawGame();
            break;
        case LAYOUT_MENU:
            drawMenu();
            break;
        case LAYOUT_GAME_OVER:
            drawGameOver();
            break;
    }
}

void App::drawGame() {
    try{
        layout3D();
        _game.update();
        _game.display();

        layout2D();
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.displayImage("cursor");
        AssetManager::Get()->_textProgram._program.use();
        _texts.getText("eggs")->renderText(_characters);
        _texts.getText("light")->renderText(_characters);
        _texts.getText("quit_button")->renderText(_characters);
        _texts.getText("move_button")->renderText(_characters);
        _texts.getText("light_button")->renderText(_characters);
        _texts.getText("grab_button")->renderText(_characters);

        if(_game.lightOn()) {
            _texts.getText("light")->changeColor(glm::vec3(0.5f, 0.5f, 0.5f));
            std::string text = "Light on (" + std::to_string(_game.light()._LIGHT_ON_TIMING - _game.light().elapsedTime()) + ")";
            _texts.getText("light")->replace(text);
        }
        if(!_game.lightOn()) {
            int time = _game.light()._LIGHT_OFF_TIMING - _game.light().elapsedTime();
            std::string text = "Light off" ;

            _texts.getText("light")->changeColor(glm::vec3(1.f, 1.f, 1.f));
            if (time > 0) {
                _texts.getText("light")->changeColor(glm::vec3(0.5f, 0.5f, 0.5f));
                text += " (" + std::to_string(_game.light()._LIGHT_OFF_TIMING - _game.light().elapsedTime()) + ")";
            }
            _texts.getText("light")->replace(text);
        }
    }

    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void App::drawMenu() {
    try{
        layout2D();
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.displayImage("menu");
        AssetManager::Get()->_textProgram._program.use();
        _texts.getText("play")->renderText(_characters);
        _texts.getText("quit")->renderText(_characters);
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void App::drawGameOver() {
    try{
        layout2D();
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.displayImage("gameover");
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void App::layout2D() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

}

void App::layout3D() {
    AssetManager::Get()->_lightProgram._program.use();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void App::layoutGame() {
    layout2D();
    try
    {
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.addImage("cursor", 0.f, 0.f, 0.1f);
        _staticImages.addImage("menu", 0.f, 0.f, 2.f);
        _staticImages.addImage("gameover", 0.f, 0.f, 2.f);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    AssetManager::Get()->_staticImageProgram._program.use();
    _staticImages.sendVertexBuffer();
    AssetManager::Get()->_textProgram._program.use();
    _characters.load();
    _texts.addText("Play (Enter)", "play", 0.5f, glm::vec2(450, 260), glm::vec3(1));
    _texts.addText("Quit (Esc)", "quit", 0.5f, glm::vec2(463, 180), glm::vec3(1));
    _texts.addText("Dragon eggs : 0", "eggs", 0.5f, glm::vec2(50, 90), glm::vec3(1));
    _texts.addText("Light off", "light", 0.5f, glm::vec2(50, 50), glm::vec3(1));
    _texts.addText("Quit (Esc)", "quit_button", 0.35f, glm::vec2(50, 670), glm::vec3(1));
    _texts.addText("Move (Z, Q, S, D)", "move_button", 0.35f, glm::vec2(50, 640), glm::vec3(1));
    _texts.addText("Light (A)", "light_button", 0.35f, glm::vec2(50, 610), glm::vec3(1));
    _texts.addText("Grab (E)", "grab_button", 0.35f, glm::vec2(50, 580), glm::vec3(1));
}


