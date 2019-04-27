#ifndef SCENEPLANET_H
#define SCENEPLANET_H

#include "source/abstractscene.h"
#include "source/engine/lfontrenderer.h"

class ScenePlanet : public AbstractScene
{
public:
    ScenePlanet();

    LFontRenderer m_fr;
    ScenePlanet(int t, int w, int h) : AbstractScene(t,w,h) {}
    void InitScene() override;
    void UpdateScene(LXM& xm, float dt) override;
    void CleanupScene() override {}


};

#endif // SCENEPLANET_H
