#include "lglobject.h"



LGLObject::LGLObject()
{

}

void LGLObject::Init(string vert, string frag, vector<string> frag_includes)
{

    // Create and compile our GLSL program from the shaders
    m_programID = LoadShaders( frag_includes, vert.c_str(), frag.c_str() );

    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    m_vertexBuffer = CreateBuffer(m_data);
    m_uvBuffer = CreateBuffer(m_uv);

}

void LGLObject::GenerateGenericPlane()
{
    m_data = {     -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,

         1.0f,  1.0f, 0.0f,
         -1.0f, 1.0f, 0.0f,
         -1.0f,  -1.0f, 0.0f,
    };

    m_uv = {     -1,-1,
         1,-1,
         1,1,

         1,1,
         -1,1,
         -1,-1,
    };

}

void LGLObject::EnableArray(int i, GLuint buf, int attr, int size)
{
    glEnableVertexAttribArray(i);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glVertexAttribPointer(
                attr,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                size,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );

}

GLuint LGLObject::CreateBuffer(vector<GLfloat> &data)
{
    GLuint buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), &data[0], GL_STATIC_DRAW);
    return buf;

}

void LGLObject::Render()
{
    glUseProgram(m_programID);
    // 1rst attribute buffer : vertices
    EnableArray(0,m_vertexBuffer,0,3);
    EnableArray(1,m_uvBuffer,1,2);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, m_data.size()/3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

}

void LGLObject::Destroy()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_uvBuffer);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);

}
