#include "../include/App.hpp"
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
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.displayImage("cursor");
        AssetManager::Get()->_textProgram._program.use();
        _texts.getText("test")->renderText(_characters);


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
    AssetManager::Get()->_multiLightsProgram._program.use();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void App::layoutGame() {
    layout2D();
    try
    {
        AssetManager::Get()->_staticImageProgram._program.use();
        _staticImages.addImage("cursor", 0.f, 0.f, 0.05f);

    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    AssetManager::Get()->_staticImageProgram._program.use();
    _staticImages.sendVertexBuffer();
    AssetManager::Get()->_textProgram._program.use();
    _characters.load();
    _texts.addText("Texte ici", "test", 0.5, glm::vec2(50, 50), glm::vec3(0.5));

}
