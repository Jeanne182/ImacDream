#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include "./../include/Camera.hpp"
#include "./../include/Mesh.hpp"
#include "./../include/GameObject.hpp"
#include "./../include/Terrain.hpp"
#include "./../include/App.hpp"
#include "./../include/Game.hpp"
#include "./../include/MapManager.hpp"
#include "./../include/AssetsManager.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    Camera camera;

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
    float ratio = (float)WINDOW_WIDTH/WINDOW_HEIGHT;


    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);



    Program program = loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "Assets/shaders/normals.fs.glsl");
    program.use();



    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);
    GLint MVP_Location = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint MV_Location = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint N_Location = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint M_Location = glGetUniformLocation(program.getGLId(), "uMMatrix");

    AssetManager::Create(argv, ProjMatrix, MVP_Location, N_Location);
//    AssetManager::Get()->_assetProgram.use();

    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    App app;

    // Application loop:
    SDL_WM_GrabInput( SDL_GRAB_ON );

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
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On nettoie la fenêtre afin de ne pas avoir de résidu du tour précédent

        app.drawGame();

        windowManager.swapBuffers();
    }

    //delete

    return EXIT_SUCCESS;
}