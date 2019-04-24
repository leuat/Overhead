#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <vector>
using namespace std;

#include <source/engine/lglobject.h>
#include <source/uniform.h>
#include <source/lxm.h>
class AbstractScene
{
public:

    glm::mat4x4 m_projMat;
    glm::mat4x4 m_viewMat;
    glm::vec3 m_camera, m_target;
    float m_time = 0;
    bool m_useFrameBuffer = false;
    GLuint m_targetFramebufferName = 0;
    GLuint m_renderedTexture;
    int m_width, m_height;
    AbstractScene() {}
    AbstractScene(int timer, int w, int h);
    ~AbstractScene();
    vector<LGLObject*> m_objects;
    vector<Uniform*> m_uniforms;

    LGLObject* m_targetObject;


    int m_timerEnd;

    void RegisterStandards(LGLObject* p1);

    void SetupFrameBuffer();

    virtual void Init();
    virtual void Update(LXM& xm);
    virtual void Cleanup();
};

#endif // ABSTRACTSCENE_H
