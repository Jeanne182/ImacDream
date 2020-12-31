#ifndef IMACDREAM_PROGRAM_HPP
#define IMACDREAM_PROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>


using namespace glimac;

class LightProgram {
private:
    GLint _M_Location, _MV_Location, _MVP_Location, _N_Location;
    GLint _ViewPos_Location, _Shininess_Location,_LightPos_Location, _LightIntensity_Location, _Texture_Location;

    GLint _Ambiant_Location, _Diffuse_Location, _Specular_Location;
public:
    Program _program;

    //CONSTRUCTOR
    LightProgram(const FilePath &applicationPath):
        _program(loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
                  applicationPath.dirPath() + "Assets/shaders/pointlight.fs.glsl")){
        _M_Location = glGetUniformLocation(_program.getGLId(), "uMMatrix");
        _MV_Location = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        _MVP_Location = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        _N_Location = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");

        //Color
        _Ambiant_Location = glGetUniformLocation(_program.getGLId(), "uAmbiant");
        _Diffuse_Location = glGetUniformLocation(_program.getGLId(), "uDiffuse");
        _Specular_Location = glGetUniformLocation(_program.getGLId(), "uSpecular");
        _Texture_Location = glGetUniformLocation(_program.getGLId(), "texture_diffuse1");

        //Lights
        _ViewPos_Location = glGetUniformLocation(_program.getGLId(), "uViewPos");
        _Shininess_Location = glGetUniformLocation(_program.getGLId(), "uShininess");
        _LightPos_Location = glGetUniformLocation(_program.getGLId(), "uLightPos_vs");
        _LightIntensity_Location = glGetUniformLocation(_program.getGLId(), "uLightIntensity");
    }

    //GETTERS
    inline GLint M_Location(){ return _M_Location; };
    inline GLint MV_Location(){ return _MV_Location; };
    inline GLint MVP_Location(){ return _MVP_Location; };
    inline GLint N_Location(){ return _N_Location; };

    inline GLint Ambiant_Location(){ return _Ambiant_Location; };
    inline GLint Diffuse_Location(){ return _Diffuse_Location; };
    inline GLint Specular_Location(){ return _Specular_Location; };
    inline GLint Texture_Location(){ return _Texture_Location; };


    inline GLint ViewPos_Location(){ return _ViewPos_Location; };
    inline GLint Shininess_Location(){ return _Shininess_Location; };
    inline GLint LightPos_Location(){ return _LightPos_Location; };
    inline GLint LightIntensity_Location(){ return _LightIntensity_Location; };
};

class StaticImageProgram{
private:
    GLuint _textureLocation;
    GLuint _M_Location;
public:
    Program _program;
    StaticImageProgram(const FilePath &applicationPath)
            : _program(loadProgram(
            applicationPath.dirPath() + "Assets/shaders/tex2D.vs.glsl",
            applicationPath.dirPath() + "Assets/shaders/tex2D.fs.glsl"))
    {
        _textureLocation = glGetUniformLocation(_program.getGLId(), "uTexture");
        _M_Location = glGetUniformLocation(_program.getGLId(), "uModelMatrix");
    }

//    //GETTERS
    inline GLint textureLocation(){ return _textureLocation; };
    inline GLint M_Location(){ return _M_Location; };
};

class SkyboxProgram {
private:
    GLint _M_Location, _MV_Location, _MVP_Location, _N_Location;
    GLint _texture_Location;
public:
    Program _program;

    //CONSTRUCTOR
    SkyboxProgram(const FilePath &applicationPath):
            _program(loadProgram(applicationPath.dirPath() + "Assets/shaders/3D.vs.glsl",
                                 applicationPath.dirPath() + "Assets/shaders/skybox.fs.glsl")){
        _M_Location = glGetUniformLocation(_program.getGLId(), "uMMatrix");
        _MV_Location = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        _MVP_Location = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        _N_Location = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
        _texture_Location = glGetUniformLocation(_program.getGLId(), "uTexture");
    }

    //GETTERS
    inline GLint M_Location(){ return _M_Location; };
    inline GLint MV_Location(){ return _MV_Location; };
    inline GLint MVP_Location(){ return _MVP_Location; };
    inline GLint N_Location(){ return _N_Location; };
    inline GLint Texture_Location(){ return _texture_Location; };
};


class WaterProgram {
private:
    GLint _M_Location, _MV_Location, _MVP_Location, _N_Location;
    GLint _ViewPos_Location, _Shininess_Location,_LightPos_Location, _LightIntensity_Location, _Texture_Location;

    GLint _Ambiant_Location, _Diffuse_Location, _Specular_Location;
public:
    Program _program;

    //CONSTRUCTOR
    WaterProgram(const FilePath &applicationPath):
            _program(loadProgram(applicationPath.dirPath() + "Assets/shaders/water.vs.glsl",
                                 applicationPath.dirPath() + "Assets/shaders/water.fs.glsl")){
        _M_Location = glGetUniformLocation(_program.getGLId(), "uMMatrix");
        _MV_Location = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
        _MVP_Location = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
        _N_Location = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");

        //Color
        _Ambiant_Location = glGetUniformLocation(_program.getGLId(), "uAmbiant");
        _Diffuse_Location = glGetUniformLocation(_program.getGLId(), "uDiffuse");
        _Specular_Location = glGetUniformLocation(_program.getGLId(), "uSpecular");
        _Texture_Location = glGetUniformLocation(_program.getGLId(), "texture_diffuse1");

        //Lights
        _ViewPos_Location = glGetUniformLocation(_program.getGLId(), "uViewPos");
        _Shininess_Location = glGetUniformLocation(_program.getGLId(), "uShininess");
        _LightPos_Location = glGetUniformLocation(_program.getGLId(), "uLightPos_vs");
        _LightIntensity_Location = glGetUniformLocation(_program.getGLId(), "uLightIntensity");
    }

    //GETTERS
    inline GLint M_Location(){ return _M_Location; };
    inline GLint MV_Location(){ return _MV_Location; };
    inline GLint MVP_Location(){ return _MVP_Location; };
    inline GLint N_Location(){ return _N_Location; };

    inline GLint Ambiant_Location(){ return _Ambiant_Location; };
    inline GLint Diffuse_Location(){ return _Diffuse_Location; };
    inline GLint Specular_Location(){ return _Specular_Location; };
    inline GLint Texture_Location(){ return _Texture_Location; };


    inline GLint ViewPos_Location(){ return _ViewPos_Location; };
    inline GLint Shininess_Location(){ return _Shininess_Location; };
    inline GLint LightPos_Location(){ return _LightPos_Location; };
    inline GLint LightIntensity_Location(){ return _LightIntensity_Location; };
};

#endif //IMACDREAM_PROGRAM_HPP
