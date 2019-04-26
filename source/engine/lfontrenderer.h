#ifndef LFONTRENDERER_H
#define LFONTRENDERER_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <ft2build.h>
#include <string>
#include <map>
#include "resources/shaders/glyph_frag.h"
#include "resources/shaders/glyph_vert.h"


#include <source/abstractscene.h>

#include FT_FREETYPE_H


#include "resources/fonts/allerta.h"


using namespace glm;
using namespace std;

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};



class LFontRenderer : public AbstractScene
{
public:
    LFontRenderer();
    void Init(char* data, int len, int size, int w, int h);
    void GenerateCharset();
    FT_Library m_ft;
    GLuint VAO, VBO;

    std::map<GLchar, Character> m_characters;
    void SetSize(int size) {
        FT_Set_Pixel_Sizes(m_face, 0, size);
    }
    LGLObject* m_lglo = nullptr;
    void RenderText(string text,GLfloat x, GLfloat y, GLfloat scalex, GLfloat scaley, glm::vec3 color);

    FT_Face m_face;
};

#endif // LFONTRENDERER_H
