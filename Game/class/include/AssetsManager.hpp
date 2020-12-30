#ifndef IMACDREAM_ASSETSMANAGER_HPP
#define IMACDREAM_ASSETSMANAGER_HPP

#include <string>
#include <glimac/common.hpp>
#include "./Model.hpp"
#include "./Program.hpp"

#include <map>


using namespace glimac;

class AssetManager {
private:
    // AssetManager Path
    FilePath _appPath;

    static AssetManager *instance;

    //Matrices
    glm::mat4 _P;

public:
    // Programs
    MultiLightsProgram _multiLightsProgram;
    StaticImageProgram _staticImageProgram;
    WaterProgram _waterProgram;

    //CONSTRUCTOR
    AssetManager(char **argv, glm::mat4 &P)
            : _appPath(argv[0]),
              _multiLightsProgram(_appPath),
              _staticImageProgram(_appPath),
              _waterProgram(_appPath),
              _P(P)
              {};

    //GETTERS
    inline FilePath appPath(){ return _appPath; };
    inline glm::mat4 P(){ return _P; };

    inline MultiLightsProgram getMultiLightsProgram(){ return _multiLightsProgram; }
    inline StaticImageProgram staticImageProgram(){ return _staticImageProgram; }


    //Singleton
    static void Create(char **argv, glm::mat4 &P)
    {
        if (!instance)
            instance = new AssetManager(argv, P);
    };

    static AssetManager *Get()
    {
        return instance;
    }

    AssetManager() = delete;
    AssetManager(AssetManager const &) = delete;
    void operator=(AssetManager const &) = delete;

    //Paths
    std::string modelFile(const std::string &model) const;
    std::string textureFile(const std::string &texture) const;
};

#endif //IMACDREAM_ASSETSMANAGER_HPP
