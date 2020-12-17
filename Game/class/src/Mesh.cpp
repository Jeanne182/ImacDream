//
// Created by matteo on 14/12/2020.
//

#include "./../include/Mesh.hpp"
#include <vector>


namespace glimac {

    void Mesh::deleteBuffers()
    {
        glDeleteBuffers(1,&_vbo);
        glDeleteBuffers(1,&_ibo);
        glDeleteVertexArrays(1,&_vao);
    }



    void Mesh::Draw() {
//        GLuint diffuseNr = 1;
//        GLuint specularNr = 1;
//        for (GLuint i = 0; i < _textures.size(); i++) {
//            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
//            // retrieve texture number (the N in diffuse_textureN)
//            std::string number;
//            std::string name = _textures[i].type;
//            std::cout << _textures[i].type << std::endl;
//
//            if (name == "texture_diffuse") {
//                number = std::to_string(diffuseNr++);
//                std::cout << number << std::endl;
//            }
//            else if (name == "texture_specular")
//                number = std::to_string(specularNr++);
//            program.use();
//            glUniform1f(glGetUniformLocation(program.getGLId(), ("material." + name + number).c_str()), i);
//            //shader.setFloat(("material." + name + number).c_str(), i);
//            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
//        }
//        glActiveTexture(GL_TEXTURE0);
//        // draw mesh
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::setupMesh() {

        //Vbo Binding, send data into the vbo, unbind
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(ShapeVertex), _vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1,&_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()*sizeof(unsigned int),_indices.data(),GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

        //Vao Binding
        glBindVertexArray(_vao);

        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_NORMAL = 1;
        const GLuint VERTEX_ATTR_TEX_COORD = 2;

        // Enable vertex attributes array
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

        // Activation of vertex attributs
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        // Define arrays of attribute data
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position)); //parametre 2 à changer en fonction du nombre d'attributs
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
        glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));

        //Debind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Debind vao
        glBindVertexArray(0);
    }
};