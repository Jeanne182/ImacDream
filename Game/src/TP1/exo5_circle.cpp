#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

class Vertex2DColor{
public:
  glm::vec2 m_position;
  glm::vec3 m_color;
  Vertex2DColor();
  Vertex2DColor(const glm::vec2 position, const glm::vec3 color);
};

Vertex2DColor::Vertex2DColor():m_position(0.0, 0.0), m_color(1.f, 1.f, 1.f){}
Vertex2DColor::Vertex2DColor(const glm::vec2 position, const glm::vec3 color):m_position(position), m_color(color){}

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 800, "GLImac");

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

     const unsigned int nombre_triangle = 100;
     const float rayon = 0.5f;

     GLuint vbo;
     glGenBuffers(1, &vbo);
     glBindBuffer(GL_ARRAY_BUFFER, vbo);


     std::vector<Vertex2DColor> vertices;

     for(unsigned int i=0; i < nombre_triangle; i++){

       vertices.push_back(Vertex2DColor(
           glm::vec2(0.0, 0.0),
           glm::vec3(1, 0, 0))
       );

       vertices.push_back(Vertex2DColor(
         glm::vec2(
           rayon*glm::cos(2*i*glm::pi<float>()/(nombre_triangle)),
           rayon*glm::sin(2*i*glm::pi<float>()/(nombre_triangle))
         ),
         glm::vec3(1.0, 0.0, 0.0))
       );

       vertices.push_back(Vertex2DColor(
         glm::vec2(
           rayon*glm::cos(2*(i+1)*glm::pi<float>()/(nombre_triangle)),
           rayon*glm::sin(2*(i+1)*glm::pi<float>()/(nombre_triangle))
         ),
         glm::vec3(1.0, 0.0, 0.0))
       );


     }


     //std::vector<Vertex2DColor> vertices{Vertex2DColor(glm::vec2(rayon*glm::cos(2*glm::pi<float>()/nombre_triangle), rayon*glm::sin(2*glm::pi<float>()/(nombre_triangle+1))), glm::vec3(1.0, 0.0, 0.0))};
     glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
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
         glDrawArrays(GL_TRIANGLES, 0, 3*nombre_triangle);
         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);

    return EXIT_SUCCESS;
}
