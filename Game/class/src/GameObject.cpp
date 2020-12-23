#include "../include/GameObject.hpp"
#include "../include/Utils.hpp"
#include <cmath>


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



// test if the camera is pointing on an object

bool GameObject::isSelected(const glm::vec3 &cameraPosition, glm::vec3 *P1, glm::vec3 *P2) {

    // Distance between the camera and the center of the interactive object
    glm::vec3 distanceVector = this->getPosition() - cameraPosition ;

    // Find the direction vector of the mouse ray
    glm::vec3 directionVectorCam = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z-1.) - cameraPosition ;

    // Distance between the camera and the center of the interactive object projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0){
        return false;
    }

    // Find the closest distance between the center of the object on the camera ray (ortho proj)
    double distanceToRay = pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector);

    // Check if the ray intersect the sphere or not depending on the radius
    if(abs(distanceToRay) > 0.5*0.5){ // mettre this->radius quand on utilisera class interactive object
        return false ;
    }

    // Distance between the first intersection point and the projection of the center on the camera ray
    double insideDistance = sqrt(0.5*0.5 - distanceToRay*distanceToRay);

    // To solve intersection points
    float t1 = distanceToCenter - insideDistance;
    float t2 = distanceToCenter + insideDistance;

    // The intersections points
    *P1 = cameraPosition + directionVectorCam*t1 ;
    *P2 = cameraPosition + directionVectorCam*t2 ;


    return true;

}
