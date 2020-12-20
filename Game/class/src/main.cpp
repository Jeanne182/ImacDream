#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include "./../include/Camera.hpp"
#include "./../include/Model.hpp"

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

    GLint uMVPMatrix_Location = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix_Location = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix_Location = glGetUniformLocation(program.getGLId(), "uNormalMatrix");


    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);
    MVMatrix = glm::translate(glm::mat4(1.), glm::vec3(0.,0.,-5.));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    /*********************************
          SPHERE (to delete later)
    *********************************/
//    Sphere sphere(1,32,32);
//    std::vector<GLuint> indices;
//    std::vector<Texture> textures;
//    std::vector<ShapeVertex> meshVertices;
//    for (GLint i = 0; i < sphere.getVertexCount();i++){
//        indices.push_back(i);
//        meshVertices.push_back(sphere.getDataPointer()[i]);
//    }
//    Mesh sphereMesh(meshVertices, indices, textures);
    Model arbre(applicationPath.dirPath() + "Assets/models/trunk.obj");


    // Application loop:
    bool done = false;
    while(!done) {

        /*********************************
          EVENT LOOP
         *********************************/

        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            camera.event(e);
            switch(e.type) {
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
            }
        }
        camera.update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On nettoie la fenêtre afin de ne pas avoir de résidu du tour précédent

        /*********************************
         MATRICES
         *********************************/

        glm::mat4 VPMatrix = ProjMatrix * camera.getViewMatrix()* glm::translate(glm::mat4(), glm::vec3(0.,0.,5.));
        glm::mat4 globalMVMatrix =  glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -5));
        glm::mat4 sphereMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime()*0, glm::vec3(0, 1, 0));

        //On modifie la valeur d'une variable uniforme
        glUniformMatrix4fv(uMVPMatrix_Location, 1, GL_FALSE, glm::value_ptr(VPMatrix *  sphereMVMatrix));
        glUniformMatrix4fv(uMVMatrix_Location, 1, GL_FALSE, glm::value_ptr(sphereMVMatrix));
        glUniformMatrix4fv(uNormalMatrix_Location, 1, GL_FALSE, glm::value_ptr(sphereMVMatrix));

        /*********************************
         RENDERING CODE
         *********************************/

        //sphereMesh.Draw(program);
        arbre.Draw(program);

        // Update the display
        windowManager.swapBuffers();
    }

    arbre.deleteBuffers();
    //sphereMesh.deleteBuffers();

    return EXIT_SUCCESS;
}