#ifndef LGLOBJECT_H
#define LGLOBJECT_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

#include <source/shader/shader.h>

class LGLObject
{
public:
    GLuint m_vertexArrayID;
    GLuint m_programID;
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    vector<GLfloat> m_data;
    vector<GLfloat> m_uv;

public:
    LGLObject();
    ~LGLObject()  { Destroy();}
    void Init(string vert, string frag,vector<string> frag_includes );
    void GenerateGenericPlane();
    void EnableArray(int i, GLuint buf, int attr, int size);
    GLuint CreateBuffer(vector<GLfloat>& data);
    void Render();
    void Destroy();
};

#endif // LGLOBJECT_H
