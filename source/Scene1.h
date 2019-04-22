#ifndef SCENE1_H
#define SCENE1_H

#include "source/abstractscene.h"
#include "source/engine/lphysics.h"

class Scene1 : public AbstractScene
{

public:
    int m_noSpheres = 64;
    LPhysics m_physics;
    Scene1(int t) : AbstractScene(t) {}
    void Init() override;
    void Update() override;
};

#endif // SCENE1_H
