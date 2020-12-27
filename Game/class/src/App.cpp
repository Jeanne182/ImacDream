#include "../include/App.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"

void App::event(const SDL_Event &e) {
    if (_layout = LAYOUT_GAME){
        _game.event(e);
    }

}

void App::draw() {
    switch(_layout){
        case LAYOUT_GAME:
            drawGame();
            break;
    }
}

void App::drawGame() {
    try{
        layout3D();
        _game.update();
        _game.display();

        layout2D();
        _staticImages.displayImage("cursor");
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void App::layout2D() {
    AssetManager::Get()->_staticImageProgram._program.use();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void App::layout3D() {
    AssetManager::Get()->_multiLightsProgram._program.use();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void App::layoutGame() {
    layout2D();
    try
    {
        _staticImages.addImage("cursor", 0.f, 0.f, 0.1f);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    _staticImages.sendVertexBuffer();
}
