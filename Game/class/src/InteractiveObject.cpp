#include "./../include/Terrain.hpp"
#include "./../include/Utils.hpp"
#include "./../include/InteractiveObject.hpp"
#include <iostream>
#include <cmath>


/*

std::vector<InteractiveObject>* InterractiveObjectsManager(const FilePath &applicationPath){
    std::vector<InteractiveObject>* objects = new std::vector<InteractiveObject>;

    //CUBE
    std::vector<GLuint> indicesCube;
    std::vector<Texture> texturesCube;
    std::vector<ShapeVertex> meshVerticesCube = {
            ShapeVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 0)),//0
            ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//1
            ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//2
            ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//3
            ShapeVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//4
            ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//5
            ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//6
            ShapeVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0))};//7


    indicesCube = {
            0, 1, 2,
            0, 1, 4,//haut
            0, 4, 3,
            4, 3, 6,//face
            4, 1, 6,
            1, 6, 5,//droite
            0, 2, 3,
            2, 3, 7,//gauche
            2, 1, 5,
            2, 5, 7,//dos
            7, 5, 3,
            5, 3, 6//bas
    };


    Mesh* cubeMesh = new Mesh(meshVerticesCube, indicesCube, texturesCube);
    InteractiveObject cubeObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *cubeMesh, 50);
    objects->push_back(cubeObject);

    return objects;
}

*/
/*
    // viewport coordinate system
    // normalized device coordinates
    float xMouse = (2. * e.button.x) / 800 - 1.; // WINDOW_WIDTH = 800
    float yMouse = 1. - (2. * e.button.y) / 600; // WINDOW_HEIGHT = 600
    float zMouse = 1.;

    glm::vec3 rayNormalizedDeviceCoordinates = glm::vec3(xMouse, yMouse, zMouse);

    // 4D homogeneous clip coordinates
    glm::vec4 rayClip = glm::vec4(rayNormalizedDeviceCoordinates.x, rayNormalizedDeviceCoordinates.y, -1., 1.);

    // 4D eye (camera) coordinates
    glm::mat4 invertedProjection = glm::inverse(ProjMatrix);
    glm::vec4 rayEye = invertedProjection * rayClip;
    glm::vec4 rayEyeCoord = glm::vec4(rayEye.x, rayEye.y, 1., 0.);

    // 4D world coordinates
    glm::mat4 invertedView = glm::inverse(camera.getViewMatrix());
    glm::vec3 rayWorldCoordinates = glm::vec3((invertedView * rayEyeCoord).x, (invertedView * rayEyeCoord).y,
                                              (invertedView * rayEyeCoord).z);
    normalize(rayWorldCoordinates);
    std::cout << "rayWorldCoordinates : " << rayWorldCoordinates << std::endl;

    glm::vec3 rayWorldCoordinatesBack = glm::vec3(rayWorldCoordinates.x, rayWorldCoordinates.y, -1.);
*/


/* Gameobject.cpp :
 #include "../include/Utils.hpp"
#include <cmath>
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

gameobject.hpp :     bool isSelected(const glm::vec3 &cameraPosition, glm::vec3 *P1, glm::vec3 *P2);


 main :

   case SDL_MOUSEBUTTONDOWN:
                    for(auto objectToFind : *objects){
                        glm::vec3 P1 = glm::vec3(0., 0., 0.);
                        glm::vec3 P2 = glm::vec3(0., 0., 0.);

                        if(objectToFind.isSelected(camera.getPosition(), &P1, &P2)){
                            std::cout << "Object selected" << std::endl;
                        }
                        else{
                            std::cout << "Object not selected" << std::endl;
                        }

                    }
                    break;




 Terrain.cpp :


    //CUBE
    std::vector<GLuint> indicesCube;
    std::vector<Texture> texturesCube;
    std::vector<ShapeVertex> meshVerticesCube = {
    ShapeVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 0)),//0
    ShapeVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//1
    ShapeVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//2
    ShapeVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//3
    ShapeVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//4
    ShapeVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//5
    ShapeVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0)),//6
    ShapeVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0))};//7


    indicesCube = {
      0, 1, 2,
      0, 1, 4,//haut
      0, 4, 3,
      4, 3, 6,//face
      4, 1, 6,
      1, 6, 5,//droite
      0, 2, 3,
      2, 3, 7,//gauche
      2, 1, 5,
      2, 5, 7,//dos
      7, 5, 3,
      5, 3, 6//bas
    };


    Mesh* cubeMesh = new Mesh(meshVerticesCube, indicesCube, texturesCube);
    GameObject cubeObject(glm::vec3(0.f,0.f,-5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *cubeMesh);
    objects->push_back(cubeObject);


*/


void InteractiveObject::setHitbox(){
    float radius = 0.0;
    for(auto *it : this->_model){

    }
}