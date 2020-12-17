#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include "./../include/Model.hpp"

using namespace glimac;

struct ModelProgram {
    Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    ModelProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "Assets/shaders/ModelLoad.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    FilePath applicationPath(argv[0]);
    //ModelProgram modelProgram(applicationPath);
    Program program = loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl", applicationPath.dirPath() + "Assets/shaders/ModelLoad.fs.glsl");
    program.use();

    GLint locationuMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locationuMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locationuNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint locationUtexture = glGetUniformLocation(program.getGLId(), "uTexture");

    float ratio = 800./600.;
    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f); //glm::perspective(angle vert de vue, ratio,near, far);

    MVMatrix = glm::translate(glm::mat4(1.),glm::vec3(0.,0.,-5.));

    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    std::string path = applicationPath.dirPath() + "Assets/cube.obj";

    Model ourModel(path);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // Update the display

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourModel.Draw(program);
        glm::mat4 MVMatrix1 = MVMatrix;
        MVMatrix1 =  glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(1, 1, 0));
        glUniformMatrix4fv(locationuMVPMatrix,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix1));
        glUniformMatrix4fv(locationuMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix1));
        glUniformMatrix4fv(locationuNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));



        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
