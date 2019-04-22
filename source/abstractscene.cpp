#include "abstractscene.h"

AbstractScene::AbstractScene(int timer)
{
    m_timerEnd = timer;
}

AbstractScene::~AbstractScene() {
    for (auto v: m_objects)
        delete v;

    for (auto v: m_uniforms)
        delete v;
}

void AbstractScene::RegisterStandards(LGLObject* p1)
{
//    printf("%d\n",p1->m_programID);
    m_uniforms.push_back(new Uniform(p1->m_programID,"camera", Uniform::tVec3));
    m_uniforms.push_back(new Uniform(p1->m_programID,"target", Uniform::tVec3));

    m_uniforms.push_back(new Uniform(p1->m_programID,"invVP", Uniform::tMat4));
    m_uniforms.push_back(new Uniform(p1->m_programID,"time", Uniform::tScalar));
//    m_uniforms.push_back(new Uniform(p1->m_programID,"projMat", Uniform::tMat4));
  //  m_uniforms.push_back(new Uniform(p1->m_programID,"viewMat", Uniform::tMat4));

}


void AbstractScene::Update() {
    for (auto v : m_objects)
        v->Render();

    for (auto u: m_uniforms)
        u->SetUniform();


}
