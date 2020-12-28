#ifndef IMACDREAM_SKYBOX_H
#define IMACDREAM_SKYBOX_H

#include "../include/GameObject.hpp"

class Skybox : public Mesh{
public:
    Skybox():Mesh(loadSkybox()._meshes[0]){};
    ~Skybox();

    Model loadSkybox();
    void Draw() const;

};


#endif //IMACDREAM_SKYBOX_H
