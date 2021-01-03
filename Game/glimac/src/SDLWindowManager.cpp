#include "glimac/SDLWindowManager.hpp"
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {
    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (_window == nullptr) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
    SDL_GL_CreateContext(_window);
    _glcontext = SDL_GL_CreateContext(_window);
//
//    SDL_WM_SetCaption(title, nullptr);
}

SDLWindowManager::~SDLWindowManager() {
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

//bool SDLWindowManager::isKeyPressed(SDLKey key) const {
//    return SDL_GetKeyState(nullptr)[key];
//}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers() {
    SDL_GL_SwapWindow(_window);
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
