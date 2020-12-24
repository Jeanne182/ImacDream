#include "../include/GameObject.hpp"

GameObject::GameObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Mesh &mesh)
    : _position(position),
            _scale(scale),
            _angles(angles),
            _mesh(&mesh)
{
    setMatrix();
}

GameObject::GameObject(const GameObject &object)
        : _position(object._position),
          _scale(object._scale),
          _angles(object._angles),
          _mesh(object._mesh)
{
    setMatrix();
}

void GameObject::display(Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location) {
    useMatrix(M_Location, MV_Location, MVP_Location, N_Location);
    _mesh->Draw(program);
}

void GameObject::setMatrix() {
    _M = glm::translate(glm::mat4(1.f), _position);
    _M = glm::scale(_M, glm::vec3(_scale));
    _M = glm::rotate(_M, glm::radians(_angles[0]), glm::vec3(1.f, 0.f, 0.f));
    _M = glm::rotate(_M, glm::radians(_angles[1]), glm::vec3(0.f, 1.f, 0.f));
    _M = glm::rotate(_M, glm::radians(_angles[2]), glm::vec3(0.f, 0.f, 1.f));
}

void GameObject::computeMatrix(const glm::mat4 &cameraView, glm::mat4 &projMatrix) {
    _MV = cameraView * _M;
    _MVP = projMatrix * _MV;
    _N = glm::transpose(glm::inverse(_MV));

}

void GameObject::useMatrix(GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location) const {
    glUniformMatrix4fv(M_Location, 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(MV_Location, 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(N_Location, 1, GL_FALSE, glm::value_ptr(_N));
}

void GameObject::deleteBuffers() {
    _mesh->deleteBuffers();
}




