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

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    Camera camera;
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;
    float ratio = (float) WINDOW_WIDTH / WINDOW_HEIGHT;

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

    GLint MVP_Location = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint MV_Location = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint N_Location = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint M_Location = glGetUniformLocation(program.getGLId(), "uMMatrix");

    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);

    std::vector<GameObject>* objects(ObjectsManager(applicationPath));
    Terrain terrain(*objects);


    // Application loop:
    bool done = false;
    while(!done) {

        //EVENTS
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            camera.event(e);
            switch(e.type) {
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On nettoie la fenêtre afin de ne pas avoir de résidu du tour précédent
        camera.update();

        //TERRAIN
        terrain.computeMatrix(camera.getViewMatrix(), ProjMatrix);
        terrain.display(program, M_Location, MV_Location, MVP_Location, N_Location);


        windowManager.swapBuffers();
    }

    terrain.deleteBuffers();
    return EXIT_SUCCESS;
}