//
// Created by matteo on 14/12/2020.
//

#include "./../include/Mesh.hpp"
#include <vector>


namespace glimac {
    // constructor
    Mesh::Mesh(std::vector<ShapeVertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) {
        this->_vertices = vertices;
        this->_indices = indices;
        this->_textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        this->setupMesh();
    };
    void Mesh::Draw(Program &program) {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for (GLuint i = 0; i < _textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = _textures[i].type;
            std::cout << _textures[i].type << std::endl;

            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
                std::cout << number << std::endl;
            }
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            program.use();
            glUniform1f(glGetUniformLocation(program.getGLId(), ("material." + name + number).c_str()), i);
            //shader.setFloat(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(ShapeVertex), &_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
                     &_indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *) 0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                              (void *) offsetof(ShapeVertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                              (void *) offsetof(ShapeVertex, texCoords));

        glBindVertexArray(0);
    }
};