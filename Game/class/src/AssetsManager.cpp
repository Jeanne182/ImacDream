#include "../include/AssetsManager.hpp"

Program AssetManager::loadShaders(const std::string &vsName, const std::string &fsName) {
    std::string vsPath = "Assets/shaders/" + vsName + ".vs.glsl";
    std::string fsPath = "Assets/shaders/" + fsName + ".fs.glsl";

    return loadProgram(_appPath.dirPath() + vsPath,
                       _appPath.dirPath() + fsPath);
}

AssetManager* AssetManager::instance= nullptr;