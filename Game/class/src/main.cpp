#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include "./../include/Camera.hpp"
#include "./../include/Mesh.hpp"

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
    std::cout<<"uMVPMatrix Location : "<< uMVPMatrix_Location<<std::endl;
    std::cout<<"uMVMatrix Location : "<< uMVMatrix_Location<<std::endl;
    std::cout<<"uNormalMatrix Location : "<< uNormalMatrix_Location<<std::endl;


    glEnable(GL_DEPTH_TEST); // Activation du test de profondeur GPU

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);
    MVMatrix = glm::translate(glm::mat4(1.), glm::vec3(0.,0.,-5.));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    int subdivisions = 32;
    Sphere sphere(1,subdivisions,subdivisions);
    int nbVertex = sphere.getVertexCount();

    /*********************************
     * VBO
     *********************************/
//    GLuint vbo; //Ou GLuint vbos[16]
//    glGenBuffers(1, &vbo); //Ou (16,vbos)
//
//    // Binding d'un VBO sur la cible GL_ARRAY_BUFFER :
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    //On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER
//
//
//    const ShapeVertex* vertices = sphere.getDataPointer();

    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i<sizeof(sphere.getDataPointer());i++){
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }

    Mesh mesh(meshVertices, indices, textures);

//    glBufferData(GL_ARRAY_BUFFER, nbVertex * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
//
//    //On débind le VBO de la cible après l'avoir modifié pour éviter de le modifier par erreur
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    /*********************************
//     * VAO
//     *********************************/
//    //Création d'un VAO
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//    //On indique à OpenGL quels attributs il va utiliser
//    const GLuint VERTEX_ATTR_POSITION = 0;
//    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //Par défaut, l'attribut position est représenté par 0
//    glVertexAttribPointer(VERTEX_ATTR_POSITION, //Index de l'attribut à spécifier
//                          3, // Nombre de composantes de l'attribut
//                          GL_FLOAT, //Type des composantes
//                          GL_FALSE, // GLboolean normalized
//                          sizeof(ShapeVertex), //Nombre d'octets séparant l'attribut pour deux sommets consécutifs
//                          (const GLvoid*)offsetof(ShapeVertex, position) //offset (en octets) de la première instance de l'attribut dans le tableau
//    );
//
//    const GLuint VERTEX_ATTR_NORMAL = 1;
//    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); //Par défaut, l'attribut position est représenté par 0
//    glVertexAttribPointer(VERTEX_ATTR_NORMAL, //Index de l'attribut à spécifier
//                          3, // Nombre de composantes de l'attribut
//                          GL_FLOAT, //Type des composantes
//                          GL_FALSE, // GLboolean normalized
//                          sizeof(ShapeVertex), //Nombre d'octets séparant l'attribut pour deux sommets consécutifs
//                          (const GLvoid*)offsetof(ShapeVertex, normal) //offset (en octets) de la première instance de l'attribut dans le tableau
//    );
//
//    const GLuint VERTEX_ATTR_TEXT = 2;
//    glEnableVertexAttribArray(VERTEX_ATTR_TEXT); //Par défaut, l'attribut position est représenté par 0
//    glVertexAttribPointer(VERTEX_ATTR_TEXT, //Index de l'attribut à spécifier
//                          3, // Nombre de composantes de l'attribut
//                          GL_FLOAT, //Type des composantes
//                          GL_FALSE, // GLboolean normalized
//                          sizeof(ShapeVertex), //Nombre d'octets séparant l'attribut pour deux sommets consécutifs
//                          (const GLvoid*)offsetof(ShapeVertex, texCoords) //offset (en octets) de la première instance de l'attribut dans le tableau
//    );
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // On débind le vbo
//    glBindVertexArray(0); // On débind le VAO

    std::string gobeletPath = applicationPath.dirPath() + "Assets/models/Arbol.obj";
    Model gobelet(gobeletPath);
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

        mesh.Draw(program);
//        glBindVertexArray(vao);
//        //On lance le pipeline sur un ensemble de sommets spécifiés par un VAO
//        glDrawArrays(GL_TRIANGLES, // Type de primitives à dessiner
//                     0, // Indice du premier sommet à dessiner
//                     nbVertex // Nombre de sommets à dessiner
//        );
//        glBindVertexArray(0);

        gobelet.Draw(program);
        // Update the display
        windowManager.swapBuffers();
    }

//    glDeleteBuffers(1, &vbo);
//    glDeleteBuffers(1, &vao);
    return EXIT_SUCCESS;
}