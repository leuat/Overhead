#ifndef LGLTEXTURE_H
#define LGLTEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

using namespace std;

class LGLTexture
{
public:
    LGLTexture() {

    }
    void Init(int w, int h, int no, string name);
    GLuint m_textureID;
    string m_name;
    int m_width, m_height, m_no;

    void Generate();
    void Bind(GLuint programID);
};

#endif // LGLTEXTURE_H
