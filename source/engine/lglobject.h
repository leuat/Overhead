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
#include <source/shader/shader.h>
#include "source/uniform.h"
#include <map>
//#include "source/engine/lgltexture.h"

using namespace glm;
using namespace std;


class LGLObject
{
public:
    GLuint m_vertexArrayID;
    GLuint m_programID;
    GLuint m_vertexBuffer;
    GLuint m_uvBuffer;
    vector<GLfloat> m_data;
    vector<GLfloat> m_uv;
    bool m_isInitialized = false;
    map<string, Uniform*> m_uniforms;
//    vector<LGLTexture*> m_textures;

public:
    LGLObject();
    ~LGLObject()  { Destroy();}
    void UseProgram();


    void Init(const char* vert, const char* frag,vector<const char*> frag_includes );
    void GenerateGenericPlane();
    void EnableArray(int i, GLuint buf, int attr, int size);
    GLuint CreateBuffer(vector<GLfloat>& data);
    void Render();
    void Destroy();
};

#endif // LGLOBJECT_H
