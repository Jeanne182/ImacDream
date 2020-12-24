#ifndef IMACDREAM_ASSETSMANAGER_HPP
#define IMACDREAM_ASSETSMANAGER_HPP

#include <string>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include "./Model.hpp"

#include <map>


using namespace glimac;

class AssetManager {
private:
    // AssetManager Path
    FilePath _appPath;

    // Models
    std::map<std::string, Model *> _models;
    static AssetManager *instance;

    //Matrices
    GLint _M_Location, _MV_Location, _MVP_Location, _N_Location;
    glm::mat4 _P;

public:
    // Programs
    Program _assetProgram;

    //CONSTRUCTOR
    inline AssetManager(char **argv, glm::mat4 &P, GLint &MVP_Location, GLint &N_Location)
            : _appPath(argv[0]),
              _assetProgram(loadShaders("3D", "normals")),
              _P(P),
              _M_Location(glGetUniformLocation(_assetProgram.getGLId(), "uMMatrix")),
              _MV_Location(glGetUniformLocation(_assetProgram.getGLId(), "uMVMatrix")),
              _MVP_Location(MVP_Location),
              _N_Location(N_Location)
              {
                _assetProgram.use();
              };

    //GETTERS
    inline FilePath appPath(){ return _appPath; };
    inline GLint M_Location(){ return _M_Location; };
    inline GLint MV_Location(){ return _MV_Location; };
    inline GLint MVP_Location(){ return _MVP_Location; };
    inline GLint N_Location(){ return _N_Location; };
    inline glm::mat4 P(){ return _P; };

    //Load program
    Program loadShaders(const std::string &vsName, const std::string &fsName);

    inline Program getAssetProgram(){ return _assetProgram; };


    //Singleton
    static void Create(char **argv, glm::mat4 &P, GLint &MVP_Location, GLint &N_Location)
    {
        if (!instance)
            instance = new AssetManager(argv, P, MVP_Location, N_Location);
    };

    static AssetManager *Get()
    {
        return instance;
    }

    AssetManager() = delete;
    AssetManager(AssetManager const &) = delete;
    void operator=(AssetManager const &) = delete;
};

#endif //IMACDREAM_ASSETSMANAGER_HPP
