#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include "./../include/Camera.hpp"
#include "./../include/Mesh.hpp"
#include "./../include/GameObject.hpp"
#include "./../include/Terrain.hpp"
#include "./../include/App.hpp"
#include "./../include/AssetsManager.hpp"
#include "./../include/Light.hpp"
#include "./../include/InteractiveObject.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    float WINDOW_WIDTH = 1080.f;
    float WINDOW_HEIGHT = 720.f;
    float ratio = WINDOW_WIDTH/WINDOW_HEIGHT;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);
    AssetManager::Create(argv, ProjMatrix);
    App app;
    app.layoutGame();
    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    SDL_SetRelativeMouseMode(SDL_TRUE );
//    SDL_WarpMouseInWindow(windowManager._window,1080/2,720/2);
    // Application loop:
    bool done = false;
    while(!done) {

        //EVENTS
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            app.event(e);

            switch(e.type) {
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym==SDLK_ESCAPE) {done = true;}
                    if (e.key.keysym.sym==SDLK_SPACE) {
                        std::cout<<"Mouse grab mode desactivated"<<std::endl;
                        SDL_SetRelativeMouseMode(SDL_FALSE );
                    }
                    if (e.key.keysym.sym==SDLK_y) {
                        std::cout<<"Mouse grab mode activated"<<std::endl;
                        SDL_SetRelativeMouseMode(SDL_TRUE );
                    }
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On nettoie la fenêtre afin de ne pas avoir de résidu du tour précédent

        app.draw();
        windowManager.swapBuffers();
    }

    app.Delete();
    return EXIT_SUCCESS;
}
