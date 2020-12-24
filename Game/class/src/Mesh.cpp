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



        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for (GLuint i = 0; i < _textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = _textures[i].type;
    void Mesh::Draw(Program &program) const{

            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            glUniform1i(glGetUniformLocation(program.getGLId(), (name + number).c_str()), i);

            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }

//        // draw mesh
        glBindVertexArray(_vao);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0 , _ubo, 0, sizeof(Material));
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Unbind
        for (size_t i = 0; i < _textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    void Mesh::setupMesh() {

        //Buffers creation
        glGenBuffers(1, &_vbo);
        glGenBuffers(1,&_ibo);
        glGenBuffers(1, &_ubo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(ShapeVertex) + sizeof(Material), _vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(_materials),(void*)(&_materials), GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        //ibo binding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()*sizeof(unsigned int),_indices.data(),GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);



        //Vao creation and binding
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

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
}