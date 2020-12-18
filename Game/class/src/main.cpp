#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>

#include <vector>
#include "./../include/FreeflyCamera.hpp"

#include "./../include/Model.hpp"

using namespace glimac;

struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uEarthTexture;
    GLint uCloudTexture;

    EarthProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "Assets/shaders/normals.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
    }
};

glm::mat4 FreeflyCamera::getViewMatrix() const{return glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);}


void FreeflyCamera::computeDirectionVectors(){
    this->m_FrontVector = glm::vec3(cos(this->m_fTheta)*sin(this->m_fPhi),
                                    sin(this->m_fTheta),
                                    cos(this->m_fTheta)*cos(this->m_fPhi));
    this->m_LeftVector = glm::vec3(sin(this->m_fPhi+M_PI/2),
                                   0,
                                   cos(this->m_fPhi+M_PI/2));
    this->m_UpVector = glm::cross(this->m_FrontVector, this->m_LeftVector);
}

void FreeflyCamera::rotateLeft(float degrees){
    m_fPhi+=glm::radians(degrees);
    computeDirectionVectors();
};

void FreeflyCamera::rotateUp(float degrees){
    m_fTheta+=glm::radians(degrees);
    computeDirectionVectors();}


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    float WINDOW_W = 1200;
    float WINDOW_H = 1000;
    SDLWindowManager windowManager(WINDOW_W, WINDOW_H, "IMAC Dream");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //Load shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
            applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
            applicationPath.dirPath() + "Assets/shaders/normals.fs.glsl"
    );
    program.use();

    //location variables uniformes
    const GLuint idProg = program.getGLId();
    GLint locationMVPMatrix = glGetUniformLocation(idProg, "uMVPMatrix");
    GLint locationMVMatrix = glGetUniformLocation(idProg, "uMVMatrix");
    GLint locationNormal = glGetUniformLocation(idProg, "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //définition du cube
    //bon chemin à garder
    // std::string cubePath = "assets/models/cube.obj";
    // Model cube(cubePath);

    //gobelet Nils
    std::string gobeletPath = applicationPath.dirPath() + "Assets/models/Arbol.obj";
    Model gobelet(gobeletPath);

    //création de la caméra
    FreeflyCamera camera;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_z))camera.moveFront(0.1);
            if(windowManager.isKeyPressed(SDLK_s))camera.moveFront(-0.1);
            if(windowManager.isKeyPressed(SDLK_q))camera.moveLeft(0.1);
            if(windowManager.isKeyPressed(SDLK_d))camera.moveLeft(-0.1);

            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
                //Ici on récupère les positions de la souris
                glm::vec2 mousePos = windowManager.getMousePosition();
                float mousePosX = mousePos.x/800.0f - 0.5;
                float mousePosY = mousePos.y/600.0f - 0.5;

                camera.rotateLeft(-2*mousePosX);
                camera.rotateUp(-2*mousePosY);
                std::cout<<"hola"<<std::endl;
            }
        }

        glm::mat4 ViewMatrix = camera.getViewMatrix();

        ProjMatrix =  glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        MVMatrix = ViewMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(
                locationMVPMatrix,
                1,
                GL_FALSE,
                glm::value_ptr(ProjMatrix * MVMatrix));

        glUniformMatrix4fv(
                locationMVMatrix,
                1,
                GL_FALSE,
                glm::value_ptr(MVMatrix));

        glUniformMatrix4fv(
                locationNormal,
                1,
                GL_FALSE,
                glm::value_ptr(NormalMatrix));

        gobelet.Draw(program);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}