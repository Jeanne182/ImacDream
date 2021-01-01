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




