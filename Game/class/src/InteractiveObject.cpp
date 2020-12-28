#include "./../include/Terrain.hpp"
#include "./../include/Utils.hpp"
#include "./../include/InteractiveObject.hpp"
#include <iostream>
#include <cmath>

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






// test if the camera is pointing on an object

bool InteractiveObject::isSelected(const glm::vec3 &cameraPosition, glm::vec3 *P1, glm::vec3 *P2) {
    std::cout << "cameraPosition : " << cameraPosition << std::endl;

    // Distance between the camera and the center of the interactive object
    glm::vec3 distanceVector = getPosition() - cameraPosition ;

    // Find the direction vector of the camera ray
    glm::vec3 directionVectorCam = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z-1.) - cameraPosition ;
    std::cout << "directionVectorCam : " << directionVectorCam << std::endl;

    // Distance between the camera and the center of the interactive object projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;
    std::cout << "distanceToCenter : " << distanceToCenter << std::endl;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0){
        return false;
    }

    // Find the closest distance between the center of the object on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));
    std::cout << "hitbox radius : " << _hitboxRadius << std::endl;
    std::cout << "distanceToRay : " << distanceToRay << std::endl;

    // Check if the ray intersect the sphere or not depending on the radius
    if(distanceToRay > _hitboxRadius){
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

