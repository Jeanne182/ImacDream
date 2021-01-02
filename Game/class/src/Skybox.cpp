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

void Skybox::useMatrix() const {
    glUniformMatrix4fv(AssetManager::Get()->_skyboxProgram.M_Location(), 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(AssetManager::Get()->_skyboxProgram.MV_Location(), 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(AssetManager::Get()->_skyboxProgram.MVP_Location(), 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(AssetManager::Get()->_skyboxProgram.N_Location(), 1, GL_FALSE, glm::value_ptr(_N));
}

void Skybox::computeMatrix(const glm::mat4 &cameraView) {

    _M = glm::translate(glm::mat4(1.f), glm::vec3(0.,0.,0.));
    _M = glm::scale(_M, glm::vec3(200.f));

    _MV = cameraView * _M;
    _MVP = AssetManager::Get()->P() * _MV;
    _N = glm::transpose(glm::inverse(_MV));

}

void Skybox::DrawSky() const {
    for (GLuint i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        glUniform1i(AssetManager::Get()->_skyboxProgram.Texture_Location(), i);

        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }

    // draw mesh
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind
    for (size_t i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
