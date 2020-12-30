#ifndef IMACDREAM_SKYBOX_H
#define IMACDREAM_SKYBOX_H

#include "../include/GameObject.hpp"

class Skybox : public Mesh{
public:
    Skybox():Mesh(loadSkybox()._meshes[0]){};
    ~Skybox();

    Model loadSkybox();
    void DrawSky() const;
    void computeMatrix(const glm::mat4 &cameraView);
    void useMatrix() const;

private:
    glm::mat4 _M, _MV, _MVP, _N;
};


#endif //IMACDREAM_SKYBOX_H
