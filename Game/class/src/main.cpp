#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>

#include <vector>
#include "./../include/TrackballCamera.hpp"

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



glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(0, 0, -m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
    return viewMatrix;
}

int main(int argc, char** argv) {
// Initialize SDL and open a window
    float WINDOW_W = 800.;
    float WINDOW_H = 600.;

    SDLWindowManager windowManager(WINDOW_W, WINDOW_H, "cc");

// Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);

/*********************************
* HERE SHOULD COME THE INITIALIZATION CODE
*********************************/


    float ratio = WINDOW_W/WINDOW_H;
    glEnable(GL_DEPTH_TEST);

//Matrices
    glm::mat4 ProjMatrix, MVMatrix, ModelMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f); //glm::perspective(angle vert de vue, ratio,near, far);
    MVMatrix = glm::translate(glm::mat4(1.),glm::vec3(0.,0.,-5.));

    TrackballCamera Camera;

    //Create a cube
    Model cube(applicationPath.dirPath() + "Assets/cube.obj");
    /*//Create a sphere
    Sphere sphere(1,32,16);
    //Create a vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    //Vbo Binding
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Send data (related to the sphere) into the VBO
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    // Unbind the VBO (to avoid errors)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //VAO creation
    GLuint vao;
    glGenBuffers(1, &vao);
    //VAO binding
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEX_COORD = 2;

    // Enable vertex attributes array
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

    // Activation of vertex attributs
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Define arrays of attribute data
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); //parametre 2 à changer en fonction du nombre d'attributs
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));

    //Debind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Debind vao
    glBindVertexArray(0);*/

    bool done = false;
    while(!done) {
        //Viewprojection matrix:
        glm::mat4 VPmatrix = ProjMatrix * Camera.getViewMatrix() * glm::translate(glm::mat4(), glm::vec3(0.,0.,5.));


        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if (windowManager.isMouseButtonPressed(SDL_BUTTON_MIDDLE))
            {
                if(e.button.button == SDL_BUTTON_WHEELUP)
                    Camera.moveFront(0.01);
                else if(e.button.button == SDL_BUTTON_WHEELDOWN)
                    Camera.moveFront(-0.01);
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
                Camera.rotateLeft((windowManager.getMousePosition().y*0.01));
                Camera.rotateUp((windowManager.getMousePosition().x*0.01));

            }
        }

        //update display
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        earthProgram.m_Program.use();

        glUniform1i(earthProgram.uEarthTexture, 0);

        glm::mat4 earthMVMatrix = MVMatrix;
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(Camera.getViewMatrix()*earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(VPmatrix * earthMVMatrix));

        cube.Draw();

        //glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

        windowManager.swapBuffers();

    }
    /*glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);*/
    cube.deleteBuffers();

    return EXIT_SUCCESS;
}