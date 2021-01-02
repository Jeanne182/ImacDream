#include "../include/GameObject.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Program.hpp>
#include "../include/Utils.hpp"

GameObject::GameObject(const glm::vec3 &position, const float &scale, const glm::vec3 &angles, Model &model, const float &hitboxRadius, const glm::vec3 &center)
    : _position(position),
            _scale(scale),
            _angles(angles),
            _model(&model),
            _hitboxRadius(hitboxRadius),
            _center(center)
{
    setMatrix();
}

GameObject::GameObject(const GameObject &object)
        : _position(object._position),
          _scale(object._scale),
          _angles(object._angles),
          _model(object._model),
          _hitboxRadius(object._hitboxRadius),
          _center(object._center)
{
    setMatrix();
}


GameObject::GameObject(const std::string &name)
                    : _position(glm::vec3(0.f,0.f,0.f)),
                    _scale(1.f),
                    _angles(glm::vec3(0.f,0.f,0.f)),
                    _model(new Model(AssetManager::Get()->modelFile(name))),
                    _hitboxRadius(1),
                    _center(glm::vec3(0.f,0.f, 0.f)){}

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
    glUniformMatrix4fv(AssetManager::Get()->_lightProgram.M_Location(), 1, GL_FALSE, glm::value_ptr(_M));
    glUniformMatrix4fv(AssetManager::Get()->_lightProgram.MV_Location(), 1, GL_FALSE, glm::value_ptr(_MV));
    glUniformMatrix4fv(AssetManager::Get()->_lightProgram.MVP_Location(), 1, GL_FALSE, glm::value_ptr(_MVP));
    glUniformMatrix4fv(AssetManager::Get()->_lightProgram.N_Location(), 1, GL_FALSE, glm::value_ptr(_N));
}

void GameObject::deleteBuffers() {
    _model->deleteBuffers();
}



void GameObject::setCenter(){
    glm::vec3 max = findMax();
    glm::vec3 min = findMin();
    _center = (max+min)/glm::vec3(2., 2., 2.);

}


void GameObject::setHitboxRadius(){

    for(auto meshes : _model->_meshes){

        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position*getScale()+getPosition());
            float radius = float(glm::distance(vertex, getCenter()));
            if(radius > _hitboxRadius ) _hitboxRadius = radius;
        }
    }
}


glm::vec3 GameObject::findMax(){
    glm::vec3 max = getPosition();
    for(auto meshes : _model->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position*getScale()+getPosition());
            if(vertex.x> max.x) max.x = vertex.x;
            if(vertex.y > max.y) max.y = vertex.y;
            if(vertex.z > max.z) max.z = vertex.z;
        }
    }
    return max;
}

glm::vec3 GameObject::findMin(){
    glm::vec3 min = getPosition();
    for(auto meshes : _model->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position*getScale()+getPosition());
            if(vertex.x< min.x) min.x = vertex.x;
            if(vertex.y < min.y) min.y = vertex.y;
            if(vertex.z < min.z) min.z = vertex.z;
        }
    }
    return min;
}




