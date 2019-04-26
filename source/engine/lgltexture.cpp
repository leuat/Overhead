#include "lgltexture.h"

void LGLTexture::Init(int w, int h, int no, string name)
{
    m_width = w;
    m_height = h;
    m_no = no;
    m_name= name;
}

void LGLTexture::Generate()
{
    glGenTextures(1, &m_textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_width, m_height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

void LGLTexture::Bind(GLuint programID) {
    glActiveTexture(GL_TEXTURE0+m_no);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glUniform1i( glGetUniformLocation(programID, m_name.c_str()), 0);
//    glUniform1i( glGetUniformLocation(m_targetObject->m_programID, "frontTexture"), 1);

}
