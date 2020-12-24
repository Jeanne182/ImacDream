#include "../include/MapManager.hpp"

void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.display(cameraView);
}

