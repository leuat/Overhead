#ifndef SCENE1_H
#define SCENE1_H
#include "resources/shaders/scene1_frag.h"
#include "resources/shaders/scene1_vert.h"
#include "resources/shaders/raymarcherinc_frag.h"

#include "source/abstractscene.h"
#include "source/engine/lphysics.h"
#include <source/engine/lfontrenderer.h>

class Scene1 : public AbstractScene
{

public:
    Scene1():AbstractScene() {}
    int m_noSpheres = 4;
    LPhysics m_physics;
    LFontRenderer m_fr;
    Scene1(int t, int w, int h) : AbstractScene(t,w,h) {}
    void InitScene() override;
    void UpdateScene(LXM& xm) override;
    void CleanupScene() override {}
};

#endif // SCENE1_H
