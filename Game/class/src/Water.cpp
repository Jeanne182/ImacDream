#include "./../include/Water.hpp"
#include "./../include/AssetsManager.hpp"
#include <chrono>
#include <random>

Water::Water():GameObject(
                glm::vec3(0.f,-0.9f,0.f),
                1.f,
                glm::vec3(0.f, 0.f, 0.f),
                *new Model(AssetManager::Get()->appPath().dirPath() + "Assets/models" + "/water.obj"),
                0,
                glm::vec3(0, 0, 0))
                {}

void Water::displayWater() {
    glUniform3fv(AssetManager::Get()->_waterProgram.Ambiant_Location(), 1, glm::value_ptr(_model->_meshes[0]._materials.Ka));
    glUniform3fv(AssetManager::Get()->_waterProgram.Diffuse_Location(), 1, glm::value_ptr(_model->_meshes[0]._materials.Kd));
    glUniform3fv(AssetManager::Get()->_waterProgram.Specular_Location(), 1, glm::value_ptr(_model->_meshes[0]._materials.Ks));

    // draw mesh
    glBindVertexArray(_model->_meshes[0]._vao);
    glDrawElements(GL_TRIANGLES, _model->_meshes[0]._indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Water::useMatrix() {
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.M_Location(), 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.MV_Location(), 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.MVP_Location(), 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(AssetManager::Get()->_waterProgram.N_Location(), 1, GL_FALSE, glm::value_ptr(_N));
    updateTime();
}

void Water::updateTime() {
    _waveTime += _waveSpeed;
    glUniform1f(AssetManager::Get()->_waterProgram.waveTime_Location(), _waveTime);
}


