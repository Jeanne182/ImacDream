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

    //Window width and height
    float _width;
    float _height;

public:

    // Programs
    MultiLightsProgram _multiLightsProgram;
    StaticImageProgram _staticImageProgram;
    TextProgram _textProgram;

    //CONSTRUCTOR
    AssetManager(char **argv, glm::mat4 &P, float &width, float &height)
            : _appPath(argv[0]),
              _multiLightsProgram(_appPath),
              _staticImageProgram(_appPath),
              _textProgram(_appPath),
              _P(P),
              _width(width),
              _height(height)
              {};

    //GETTERS
    inline FilePath appPath(){ return _appPath; };
    inline glm::mat4 P(){ return _P; };
    inline float getWidth(){ return _width; };
    inline float getHeight(){ return _height; };

    inline MultiLightsProgram getMultiLightsProgram(){ return _multiLightsProgram; }
    inline StaticImageProgram getstaticImageProgram(){ return _staticImageProgram; }
    inline TextProgram getTextProgram(){ return _textProgram; }


    //Singleton
    static void Create(char **argv, glm::mat4 &P, float &width, float &height)
    {
        if (!instance)
            instance = new AssetManager(argv, P, width, height);
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
