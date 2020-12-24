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
#include "./../include/Light.hpp"


using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    Camera camera;
    int WINDOW_WIDTH = 1200;
    int WINDOW_HEIGHT = 1000;
    float ratio = (float) WINDOW_WIDTH / WINDOW_HEIGHT;

    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAC dream");

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
                                  applicationPath.dirPath() + "Assets/shaders/pointlight.fs.glsl"); //directionallights
    program.use();

    GLint MVP_Location = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint MV_Location = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint N_Location = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint M_Location = glGetUniformLocation(program.getGLId(), "uMMatrix");
    GLint ViewPos_Location = glGetUniformLocation(program.getGLId(), "uViewPos");
    GLint Shininess_Location = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint LightPos_Location = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    GLint LightIntensity_Location = glGetUniformLocation(program.getGLId(), "uLightIntensity");

    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 10000.f);

    std::vector<GameObject>* objects(ObjectsManager(applicationPath));

    Light pointLight(camera.getViewMatrix());

    Terrain terrain(*objects);

    //TREE
//    std::string pathModelTree = applicationPath.dirPath() + "Assets/models/arbre.obj";
//    Model* tree = new Model(pathModelTree);
    //GameObject treeObject(glm::vec3(5.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), tree->_meshes[0]);
    //objects->push_back(treeObject);

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
                case SDL_KEYDOWN:
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
        camera.update();
        glUniform3fv(ViewPos_Location, 1, glm::value_ptr( camera.getPosition()));

        glUniform1f(Shininess_Location, pointLight.getShininess()); // taille de la tache glossy
        glUniform3fv(LightPos_Location, 1, glm::value_ptr(pointLight.getPosition()));
        glUniform3fv(LightIntensity_Location, 1, glm::value_ptr(pointLight.getIntensity()));

        //TERRAIN
        terrain.computeMatrix(camera.getViewMatrix(), ProjMatrix);
        terrain.display(program, M_Location, MV_Location, MVP_Location, N_Location);

        // tree->Draw(program);
        windowManager.swapBuffers();
    }

    terrain.deleteBuffers();
    return EXIT_SUCCESS;
}