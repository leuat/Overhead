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
    m_fr.RenderText("YO",0.3,0.4,0.003f,0.006f,vec3(1,1,1));

//    m_frontTextureID =  m_fr.m_renderTexture.m_textureID;
    m_frontTextureID =  m_fr.m_renderedTexture;

    RegisterStandards(p1);
    SetupFrameBuffer();
    m_targetObject->m_uniforms["lamp"]->m_fval = 0.7;
    m_targetObject->m_uniforms["lsca"]->m_fval = 500;

    m_targetObject->m_uniforms["chromatic"]->m_fval = 0.03;//0.03*sin(m_time/60.0);

    p1->m_uniforms["aamp1"] = new Uniform(p1->m_programID,"aamp1",Uniform::tScalar);

}


void ScenePlanet::UpdateScene(LXM &xm, float dt)
{
    AbstractScene::UpdateScene(xm, dt);

    m_objects[0]->m_uniforms["camera"]->m_vec3 = m_camera;
    m_objects[0]->m_uniforms["target"]->m_vec3 = m_target;

    float r = 8;
    float r2 = 10 + cos(m_time/56.34)*6;
    float t = m_time/60.0 ;
//    m_camera  = glm::vec3(cos(t)*r,  0.5*(cos(t*0.3)*r + r*1.3), sin(t)*r);
    m_camera  = glm::vec3(cos(t)*r, sin(t)*r2,cos(t)*r);
//    m_target = vec3(3*(cos(1.12*t)),3*(sin(1.3*t)),2*(sin(0.7*t)))*0.2;
    t = t + 2;
    m_target  = glm::vec3(cos(t)*r,  sin(t)*r2,cos(t)*2)*0.5;
//

    float var1 = sin(m_time*2.34);
    float var2 = sin(m_time*1.23);
    SetForegroundColor(glm::vec3(1,1,1)*sin(m_time/8.0));

    m_objects[0]->m_uniforms["time"]->m_fval = m_time;

    m_objects[0]->m_uniforms["aamp1"]->m_fval = 0.1*(sin(m_time/50.23)+1);
    SetScreenColor(glm::vec3(1,1,1));

}
