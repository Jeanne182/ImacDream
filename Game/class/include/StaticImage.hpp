#ifndef IMACDREAM_STATICIMAGE_HPP
#define IMACDREAM_STATICIMAGE_HPP

#include <iostream>
#include <glimac/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <map>


using namespace glimac;

class StaticImage {
public:
    std::string _filename;
    std::unique_ptr<Image> _imgPtr;
    GLuint *_texture;
    std::vector<Vertex2DUV> _vertices;
    glm::mat3 _modelMatrix;
    glm::mat3 _computedMatrix;
    float _x, _y, _scale;

};

class StaticImageManager {
private:

    GLuint _vbo, _vao, _ibo;
public:
    std::map<const std::string, StaticImage *> _images;
    StaticImageManager();
    ~StaticImageManager();
    StaticImage* getStaticImage(const std::string &imageName) const;
    void addImage(const std::string &filename, const float &x, const float &y, const float &scale);
    void setupImage(StaticImage *img);
    void moveImage(const std::string &filename, const float &x, const float &y, const float &scale) const;
    void sendVertexBuffer() const;
    void displayImage(const std::string &imageName) const;
    void setScale(const std::string &imageName, const float &scale) const;
    static void computeMatrix(StaticImage *img) ;
};




#endif //IMACDREAM_STATICIMAGE_HPP
