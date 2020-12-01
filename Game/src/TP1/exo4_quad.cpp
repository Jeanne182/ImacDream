#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>

using namespace glimac;

class Vertex2DColor{
public:
  glm::vec2 m_position;
  glm::vec3 m_color;
  Vertex2DColor();
  Vertex2DColor(const glm::vec2 position, const glm::vec3 color);
};

Vertex2DColor::Vertex2DColor():m_position(0.0, 0.0), m_color(0.f, 0.f, 0.f){}
Vertex2DColor::Vertex2DColor(const glm::vec2 position, const glm::vec3 color):m_position(position), m_color(color){}

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

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl", applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    program.use();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     GLuint vbo;
     glGenBuffers(1, &vbo);

     glBindBuffer(GL_ARRAY_BUFFER, vbo);
     Vertex2DColor vertices[] = {
       Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1, 0, 0)),
       Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0, 1, 0)),
       Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 0, 1)),
       Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(1, 0, 0)),
       Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0, 1, 0)),
       Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 0, 1))
     };
     glBufferData(GL_ARRAY_BUFFER, 6*sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     GLuint vao;
     glGenBuffers(1, &vao);
     glBindVertexArray(vao);
     const GLuint VERTEX_ATTR_POSITION = 3;
     const GLuint VERTEX_ATTR_COLOR = 8;
     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
     glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
     glBindBuffer(GL_ARRAY_BUFFER, vbo);
     glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_position));
     glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_color));
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);



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

         glClear(GL_COLOR_BUFFER_BIT);
         glBindVertexArray(vao);
         glDrawArrays(GL_TRIANGLES, 0, 6);
         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);

    return EXIT_SUCCESS;
}
