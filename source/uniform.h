#ifndef UNIFORM_H
#define UNIFORM_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Include GLFW
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
// Include GLM
#include <glm/glm.hpp>
#include <algorithm>
#include <string>

using namespace std;
using namespace glm;


class Uniform {
public:
    enum UType { tVec3, tMat3, tMat4, tScalar };
    Uniform(GLuint prog, string name, UType t) {
        GetUniform(prog, name, t);
        m_name = name;
    }
    string m_name;
    UType m_type;
    glm::mat4 m_mat4;
    glm::mat3 m_mat3;
    glm::vec3 m_vec3;
    GLfloat m_fval;
    GLuint m_id;
    void GetUniform(GLuint program, string name, UType t) {
        m_id = glGetUniformLocation(program, name.c_str());
        m_type = t;
    }
    void SetUniform() {
        if (m_type==tVec3) glUniform3f(m_id, m_vec3.x,m_vec3.y,m_vec3.z);
        if (m_type==tScalar) glUniform1f(m_id, m_fval);
        if (m_type==tMat4) {
            glUniformMatrix4fv(m_id, 1, GL_FALSE, &m_mat4[0][0]);
         //   printf(": %s, %d\n", m_name.c_str(), m_id);
        }
        if (m_type==tMat3) glUniformMatrix3fv(m_id, 1, GL_FALSE, &m_mat3[0][0]);
    }

};

#endif // UNIFORM_H
