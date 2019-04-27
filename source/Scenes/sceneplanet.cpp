#include "sceneplanet.h"

ScenePlanet::ScenePlanet()
{

}

void ScenePlanet::InitScene()
{
    AbstractScene::InitScene();

   LGLObject* p1 = new LGLObject();
   p1->GenerateGenericPlane();
   vector<const char*> includes;
   includes.push_back(LShaders::raymarcherinc);
   p1->Init(LShaders::scenePlanet_vert,LShaders::scenePlanet_frag, includes);

   m_objects.push_back(p1);

    m_fr.Init(LFont::allerta, LFont::fontSize,64, m_width, m_height);
    m_fr.RenderText("YO",0.1,0.4,0.003f,0.006f,vec3(1,1,1));

//    m_frontTextureID =  m_fr.m_renderTexture.m_textureID;
    m_frontTextureID =  m_fr.m_renderedTexture;

    RegisterStandards(p1);
    SetupFrameBuffer();
}


void ScenePlanet::UpdateScene(LXM &xm)
{
    AbstractScene::UpdateScene(xm);

    m_objects[0]->m_uniforms["camera"]->m_vec3 = m_camera;
    m_objects[0]->m_uniforms["target"]->m_vec3 = m_target;

    float r = 6;
    float t = m_time/60.0 ;
    m_camera  = glm::vec3(cos(t)*r,0.5*(cos(t*0.3)*r + r*1.3),sin(t)*r);
    m_target = vec3(0,3*(2+sin(1.3*t)),0);


    float var1 = sin(m_time*2.34);
    float var2 = sin(m_time*1.23);
    SetForegroundColor(glm::vec3(1,1,1)*(rand()%100/100.0f));

    SetScreenColor(glm::vec3(1,1,1));

    m_targetObject->m_uniforms["chromatic"]->m_fval = 0.03;//0.03*sin(m_time/60.0);
    m_time++;

}
