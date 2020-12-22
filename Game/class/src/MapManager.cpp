#include "../include/MapManager.hpp"

void MapManager::display(glm::mat4 &cameraView, glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location,
                    GLint &N_Location) {
    _terrain.display(cameraView, projMatrix, program, M_Location, MV_Location, MVP_Location, N_Location);
}
