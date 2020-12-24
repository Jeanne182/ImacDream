#include "../include/GameObject.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Program.hpp>

GameObject::GameObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Model &model)
    : _position(position),
            _scale(scale),
            _angles(angles),
            _model(&model)
{
    setMatrix();
}

GameObject::GameObject(const GameObject &object)
        : _position(object._position),
          _scale(object._scale),
          _angles(object._angles),
          _model(object._model)
{
    setMatrix();
}

void GameObject::display() {
    useMatrix();
    _model->Draw();
}

void GameObject::setMatrix() {
    _M = glm::translate(glm::mat4(1.f), _position);
    _M = glm::scale(_M, glm::vec3(_scale));
    _M = glm::rotate(_M, glm::radians(_angles[0]), glm::vec3(1.f, 0.f, 0.f));
    _M = glm::rotate(_M, glm::radians(_angles[1]), glm::vec3(0.f, 1.f, 0.f));
    _M = glm::rotate(_M, glm::radians(_angles[2]), glm::vec3(0.f, 0.f, 1.f));
}

void GameObject::computeMatrix(const glm::mat4 &cameraView) {
    _MV = cameraView * _M;
    _MVP = AssetManager::Get()->P() * _MV;
    _N = glm::transpose(glm::inverse(_MV));
}

void GameObject::update(const glm::mat4 &cameraView) {
    setMatrix();
    computeMatrix(cameraView);
    display();

}

void GameObject::useMatrix() const {
    glUniformMatrix4fv(AssetManager::Get()->_multiLightsProgram.M_Location(), 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(AssetManager::Get()->_multiLightsProgram.MV_Location(), 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(AssetManager::Get()->_multiLightsProgram.MVP_Location(), 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(AssetManager::Get()->_multiLightsProgram.N_Location(), 1, GL_FALSE, glm::value_ptr(_N));
}

void GameObject::deleteBuffers() {
    _model->deleteBuffers();
}




