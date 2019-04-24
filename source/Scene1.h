#ifndef SCENE1_H
#define SCENE1_H

#include "source/abstractscene.h"
#include "source/engine/lphysics.h"

class Scene1 : public AbstractScene
{

public:
    int m_noSpheres = 4;
    LPhysics m_physics;
    Scene1(int t, int w, int h) : AbstractScene(t,w,h) {}
    void Init() override;
    void Update(LXM& xm) override;
};

#endif // SCENE1_H
