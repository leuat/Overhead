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
    Uniform(GLuint prog, string name, int size) {
        GetUniform(prog, name, tScalar);
        m_name = name;
        m_arrSize = size;
        m_arr = new float[size];
    }
    Uniform() {

    }
    string m_name;
    UType m_type;
    glm::mat4 m_mat4;
    glm::mat3 m_mat3;
    glm::vec3 m_vec3;
    GLfloat m_fval;
    GLfloat* m_arr;
    int m_arrSize = 1;
    GLuint m_id;
    void GetUniform(GLuint program, string name, UType t) {
        m_id = glGetUniformLocation(program, name.c_str());
        m_type = t;
    }
    void SetUniform();

};

#endif // UNIFORM_H
