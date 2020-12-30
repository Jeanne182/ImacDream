#ifndef IMACDREAM_TEXT_HPP
#define IMACDREAM_TEXT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
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


// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

//std::map<GLchar, Character> Characters;



class Text {
public:
    std::string _text;
    glm::mat3 _modelMatrix;
    glm::mat3 _computedMatrix;
};




class TextManager{
private :
    GLuint _vbo, _vao;

public :
    std::map<GLchar, Character> Characters;


    //std::map<const std::string, Text *> _allTexts;
    //TextManager();
    //~TextManager();
    //Text* getText(const std::string &text) const;
    void loadCharacters();
    //void moveText(const std::string &text, const float &x, const float &y, const float &scale);
    void displayText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) const;
    //void setScale(const std::string &text, const float &scale) const;
    //void setTranslation(const std::string &text, const float x, const float y) const;
    //void computeMatrix(const std::string &text) const;
    //void computeMatrix(Text *txt) const;

};

#endif //IMACDREAM_TEXT_HPP
