#ifndef SCENE1_H
#define SCENE1_H

#include "source/abstractscene.h"

class Scene1 : public AbstractScene
{
public:
    Scene1(int t) : AbstractScene(t) {}
    float m_time = 0;
    void Init() override;
    void Update() override;
};

#endif // SCENE1_H
