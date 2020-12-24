#ifndef IMACDREAM_PROGRAM_HPP
#define IMACDREAM_PROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>


using namespace glimac;

class AssetProgram {
private:
    GLint _M_Location, _MV_Location, _MVP_Location, _N_Location;
public:
    Program _program;

    //CONSTRUCTOR
    AssetProgram(const FilePath &applicationPath):
        _program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                  applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")){
        _M_Location = glGetUniformLocation(_program.getGLId(), "uMMatrix");
        _MV_Location = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        _MVP_Location = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        _N_Location = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
    }

    //GETTERS
    inline GLint M_Location(){ return _M_Location; };
    inline GLint MV_Location(){ return _MV_Location; };
    inline GLint MVP_Location(){ return _MVP_Location; };
    inline GLint N_Location(){ return _N_Location; };
};


#endif //IMACDREAM_PROGRAM_HPP
