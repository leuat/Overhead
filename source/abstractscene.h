#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <vector>
using namespace std;

#include <source/engine/lglobject.h>
#include <source/uniform.h>

class AbstractScene
{
public:

    glm::mat4x4 m_projMat;
    glm::mat4x4 m_viewMat;
    glm::vec3 m_camera, m_target;

    AbstractScene(int timer);
    ~AbstractScene();
    vector<LGLObject*> m_objects;
    vector<Uniform*> m_uniforms;

    int m_timerEnd;

    void RegisterStandards(LGLObject* p1);

    virtual void Init() {}
    virtual void Update();
    virtual void Cleanup() {}
};

#endif // ABSTRACTSCENE_H
