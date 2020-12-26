#include "../include/AssetsManager.hpp"

AssetManager* AssetManager::instance= nullptr;


std::string AssetManager::modelFile(const std::string &model) const {
    return _appPath.dirPath() + "../../Assets/models/" + model;
}

std::string AssetManager::textureFile(const std::string &texture) const {
    return _appPath.dirPath() + "../../Assets/textures/" + texture;
}

