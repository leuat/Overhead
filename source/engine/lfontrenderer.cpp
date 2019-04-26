#include "lfontrenderer.h"

LFontRenderer::LFontRenderer()
{

}

void LFontRenderer::Init(char* data, int len, int size, int w, int h)
{
    if (FT_Init_FreeType(&m_ft))
        printf( "ERROR::FREETYPE: Could not init FreeType Library\n");
    if (FT_New_Memory_Face(m_ft, (FT_Byte*)data, len,  0, &m_face))
        printf("ERROR::FREETYPE: Failed to load font\n");;

    m_width = w;
    m_height = h;

    SetSize(size);

    GenerateCharset();
    InitFrameBufferOnly();

}

void LFontRenderer::GenerateCharset()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
#ifdef IS_DEBUG
        {
            printf("ERROR::FREETYTPE: Failed to load Glyph\n");;
            continue;
        }
#endif
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
            glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
            (GLuint)m_face->glyph->advance.x
        };
        m_characters.insert(std::pair<GLchar, Character>(c, character));
    }
//    FT_Done_Face(m_face);
  //  FT_Done_FreeType(m_ft);

//    return;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    m_lglo = new LGLObject();
    m_lglo->GenerateGenericPlane();
//    m_lglo->Init("../resources/shaders/glyph.vert","../resources/shaders/glyph.frag", vector<string>() );
    m_lglo->Init(glyph_vert,glyph_frag, vector<const char*>() );
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void LFontRenderer::RenderText(string text, GLfloat x, GLfloat y, GLfloat scalex, GLfloat scaley, glm::vec3 color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 //   if (!m_lglo->m_isInitialized)
   //     return;
  //  glDisable(GL_BLEND);
//    return;
    if (m_useFrameBuffer)
        glBindFramebuffer(GL_FRAMEBUFFER, m_targetFramebufferName);


    m_lglo->UseProgram();

        glUniform3f(glGetUniformLocation(m_lglo->m_programID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        // Iterate through all characters
        std::string::const_iterator c;
        glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

        glUniformMatrix4fv(glGetUniformLocation(m_lglo->m_programID, "projection"),1,GL_FALSE,&projection[0][0]);

        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = m_characters[*c];

            GLfloat xpos = x + ch.Bearing.x * scalex;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scaley;

            GLfloat w = ch.Size.x * scalex;
            GLfloat h = ch.Size.y * scaley;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scalex; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);

        if (m_useFrameBuffer) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

        }


}
