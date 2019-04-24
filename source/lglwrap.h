#ifndef LGLWRAP_H
#define LGLWRAP_H

#define GLM_ENABLE_EXPERIMENTAL
// Include GLEW
#define GLEW_STATIC

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
using namespace glm;

#include <source/shader/shader.h>
#include <source/lxm.h>

#include <vector>
#include <source/abstractscene.h>

using namespace std;


class LGLWrap
{
protected:
    GLFWwindow* m_window;
    LXM* m_lxm;
    int m_timer;

    AbstractScene* m_currentScene = nullptr;

public:
    vector<AbstractScene*> m_scenes;

    LGLWrap(LXM* lxm);

    int Init(int w, int h);
    void Update();

    int Exec();
};



#endif // LGLWRAP_H
