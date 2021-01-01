#ifndef IMACDREAM_TEXT_HPP
#define IMACDREAM_TEXT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <glimac/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <map>
#include <utility>

using namespace glimac;

struct Character{
    GLuint _textureID;
    glm::ivec2 _size;
    glm::ivec2 _bearing;
    FT_Pos _advance;
};

class CharactersManager{
private:
    std::map<char, Character> _characters;

public:
    CharactersManager() = default;
    ~CharactersManager() = default;

    void load();
    void Delete();
    inline std::map<char, Character> getCharacters() const noexcept {return _characters;};
};



class Text{
private :
    GLuint _vbo, _vao;
    std::string _text, _name;
    float _scale;
    glm::vec2 _pos;
    glm::vec3 _color;
    glm::mat4 _projection_matrix;


public:

    Text() = default;
    ~Text() = default;


    //SETTERS
    inline void setText(const std::string &text){ _text = std::move(text) ; };
    inline void setName(const std::string &name){ _name = std::move(name) ; };
    inline void setPosition(const glm::vec2 &pos){ _pos = pos ;};
    inline void setScale(const float &scale){ _scale = scale ; };
    inline void setColor(const glm::vec3 &color){ _color = color ;};
    inline void setProjMatrix(const glm::mat4 &proj){ _projection_matrix = proj ;};

    //GETTERS
    inline std::string getName(){ return _name; };
    inline std::string getText(){ return _text; };
    inline GLuint getVAO(){ return _vao; };
    inline GLuint getVBO(){ return _vbo; };
    inline float getScale(){ return _scale; };
    inline glm::vec2 getPosition(){ return _pos; };
    inline glm::vec3 getColor(){ return _color; };
    inline glm::mat4 getProjMatrix(){ return _projection_matrix; };


    //METHODS
    void Initialization();
    void DeleteText() ;
    void renderText(const CharactersManager &characters);


};


class TextsManager{
private :
    std::map<const std::string, Text*> _allTexts;
public:
    TextsManager()=default ;
    ~TextsManager() = default;


    //GETTERS
    Text* getText(const std::string &name) const;

    //METHODS
    void addText(const std::string &text, const std::string &name, const float &scale, const glm::vec2 &pos, const glm::vec3 &color);
    void Delete();


};

#endif //IMACDREAM_TEXT_HPP
