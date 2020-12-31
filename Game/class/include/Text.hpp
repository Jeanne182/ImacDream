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

class Text{
private:
    std::map<char, Character> _characters;

public:
    Text() = default;
    ~Text();

    void load();
    inline std::map<char, Character> getCharacters() const noexcept {return _characters;};
};



class TextManager{
private :
    GLuint _vbo, _vao;
    std::string _text;
    float _scale;
    glm::vec2 _pos;
    glm::vec3 _color;
    glm::mat4 _projection_matrix;
    std::vector<Text*> _allTexts;


public:
    TextManager() = default;
    ~TextManager();

    void Initialization(std::string text, const float &scale=1.0,
                        const glm::vec2 &pos = glm::vec2(0.), const glm::vec3 &color = glm::vec3(1.));

    //SETTERS
    inline void setText(std::string text){ _text = std::move(text) ; };
    inline void setPosition(const glm::vec2 &pos){ _pos = pos ;};
    inline void setScale(const float &scale){ _scale = scale ; };
    inline void setColor(const glm::vec3 &color){ _color = color ;};

    //METHODS
    void renderText(const Text& text);
    Text* getText();

};

#endif //IMACDREAM_TEXT_HPP
