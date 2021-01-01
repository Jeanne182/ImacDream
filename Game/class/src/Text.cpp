#include "../include/Text.hpp"
#include "../include/AssetsManager.hpp"
#include <iostream>

void Text::Initialization(){
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::DeleteText() {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}


void Text::renderText(const CharactersManager &characters) {

    // Activate corresponding render state
    glUniform3f(AssetManager::Get()->_textProgram.textColor_Location(),_color.x, _color.y, _color.z);
    glUniformMatrix4fv(AssetManager::Get()->_textProgram.Projection_Location(), 1, GL_FALSE, glm::value_ptr(_projection_matrix));


    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);
    float x =_pos.x;
    float y = _pos.y;

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = _text.begin(); c !=_text.end(); c++)
    {
        Character ch = characters.getCharacters()[*c];

        float xpos = x + ch._bearing.x * _scale;
        float ypos = y - (ch._size.y - ch._bearing.y) * _scale;

        float w = ch._size.x * _scale;
        float h = ch._size.y * _scale;
        // Update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch._textureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch._advance >> 6) * _scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void CharactersManager::load() {
    // TUTO : https://learnopengl.com/In-Practice/Text-Rendering


    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        std::cerr << "ERROR::FREETYPE: Could not init Freetype Library" << std::endl;
        exit(EXIT_FAILURE);
    }

    FT_Face face;
    if(FT_New_Face(ft, "Assets/fonts/arial.ttf", 0, &face))
    {
        std::cerr << "ERROR::FREETYPE: Failed to load font assets/fonts/Love_Craft.ttf" << std::endl;
        exit(EXIT_FAILURE);
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };
        _characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void CharactersManager::Delete() {
    // Deletes all the textures generated for each character
    for(auto& character: _characters)
        glDeleteTextures(1, &character.second._textureID);
}


void TextsManager::addText(const std::string &text, const std::string &name, const float &scale, const glm::vec2 &pos, const glm::vec3 &color) {
    Text* newText = new Text;
    newText->setText(text) ;
    newText->setName(name);
    newText->setScale(scale);
    newText->setPosition(pos);
    newText->setColor(color);
    newText->setProjMatrix(glm::ortho(0.f, AssetManager::Get()->getWidth(), 0.f, AssetManager::Get()->getHeight()));

    _allTexts.insert(std::pair<std::string, Text*>(newText->getName(), newText));
    newText->Initialization();
}

Text* TextsManager::getText(const std::string &name) const {
    return (Text*)_allTexts.find(name)->second;
}

void TextsManager::Delete() {
    std::map<const std::string, Text *>::const_iterator it;
    for (it = _allTexts.begin(); it != _allTexts.end(); ++it)
    {
       it->second->DeleteText();
    }
}