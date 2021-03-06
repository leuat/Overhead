#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

using namespace std;
#include <vector>

#include <source/engine/lglobject.h>
#include <source/uniform.h>
#include <source/lxm.h>
#include <map>




class AbstractScene
{
public:

    glm::mat4x4 m_projMat;
    glm::mat4x4 m_viewMat;
    glm::vec3 m_camera, m_target;

    float m_time = 0;
    bool m_useFrameBuffer = false;
    GLuint m_targetFramebufferName = 0;
//    GLuint m_renderedTexture;
    GLuint m_renderedTexture;
    int m_width, m_height;
    AbstractScene() {}
    AbstractScene(int timer, int w, int h);
    ~AbstractScene();
    vector<LGLObject*> m_objects;

    void SetForegroundColor(vec3 col);
    void SetScreenColor(vec3 col);

    LGLObject* m_targetObject;

    GLuint m_frontTextureID = -1;
    int m_timerEnd;
    int m_foregroundColorID = -1;
    int m_screenColorID = -1;
    void RegisterStandards(LGLObject* p1);

    void InitFrameBufferOnly();
    void SetupFrameBuffer();

    virtual void InitScene();
    virtual void UpdateScene(LXM& xm, float dt);
    virtual void CleanupScene();
};

#endif // ABSTRACTSCENE_H
