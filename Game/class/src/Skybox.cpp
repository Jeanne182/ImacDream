#include "../include/Skybox.hpp"
#include "../include/AssetsManager.hpp"

Model Skybox::loadSkybox(){
    std::string modelsPath = AssetManager::Get()->appPath().dirPath() + "Assets/models";
    auto* skyModel = new Model(modelsPath + "/skybox.obj");
    return *skyModel;
}

Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}

void Skybox::Draw() const {

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        glUniform1i(glGetUniformLocation(AssetManager::Get()->_skyboxProgram._program.getGLId(), (name + number).c_str()), i);

        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }
    AssetManager::Get()->_skyboxProgram._program.use();

    // draw mesh
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
