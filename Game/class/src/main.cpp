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


using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    float WINDOW_WIDTH = 800.f;
    float WINDOW_HEIGHT = 600.f;
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

    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU
    SDL_WM_GrabInput( SDL_GRAB_ON );

    Light pointLight(app._game._camera.getViewMatrix());

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
                    if (e.key.keysym.sym==SDLK_a)
                    {
                        if(!pointLight.getLightOn()){
                            pointLight.setIntensity(70.);
                            pointLight.setLightOn(true);}
                        else{
                            pointLight.setIntensity(20.);
                            pointLight.setLightOn(false);
                        }
                    };
                    break;

            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On nettoie la fenêtre afin de ne pas avoir de résidu du tour précédent
        glUniform3fv(AssetManager::Get()->_multiLightsProgram.ViewPos_Location(), 1, glm::value_ptr( app._game._camera.getPosition()));

        app.draw();
        glUniform1f(AssetManager::Get()->_multiLightsProgram.Shininess_Location(), pointLight.getShininess()); // taille de la tache glossy
        glUniform3fv(AssetManager::Get()->_multiLightsProgram.LightPos_Location(), 1, glm::value_ptr(pointLight.getPosition()));
        glUniform3fv(AssetManager::Get()->_multiLightsProgram.LightIntensity_Location(), 1, glm::value_ptr(pointLight.getIntensity()));
        windowManager.swapBuffers();
    }

    app.Delete();
    return EXIT_SUCCESS;
}