#include "Scene1.h"



void Scene1::InitScene()
{
    AbstractScene::InitScene();

   LGLObject* p1 = new LGLObject();
   p1->GenerateGenericPlane();
   vector<const char*> includes;
   includes.push_back(LShaders::raymarcherinc);
   p1->Init(LShaders::scene1_vert,LShaders::scene1_frag, includes);

   m_objects.push_back(p1);

//    m_fr.Init(LFont::allerta, sizeof(LFont::allerta),64, m_width, m_height);
    m_fr.Init(LFont::allerta, LFont::fontSize,64, m_width, m_height);
    m_fr.RenderText("PROXIMA",0.1,0.4,0.003f,0.006f,vec3(1,1,1));

//    m_frontTextureID =  m_fr.m_renderTexture.m_textureID;
    m_frontTextureID =  m_fr.m_renderedTexture;

    RegisterStandards(p1);
    float r= 10;
    m_physics.InitRandom(m_noSpheres,vec3(r,r,r),vec3(r/2,0,r/2));
    p1->m_uniforms["spherePos" ]  = new Uniform(p1->m_programID,"spherePos",m_noSpheres*5);



   //m_projMat = getProjectionMatrix();
  // m_viewMat = getViewMatrix();
    SetupFrameBuffer();
}

void Scene1::UpdateScene(LXM& xm, float dt)
{
    AbstractScene::UpdateScene(xm, dt);

    m_objects[0]->m_uniforms["camera"]->m_vec3 = m_camera;
    m_objects[0]->m_uniforms["target"]->m_vec3 = m_target;

    float r = 6;
    float t = m_time/60.0 ;
    m_camera  = glm::vec3(cos(t)*r,0.5*(cos(t*0.3)*r + r*1.3),sin(t)*r);
//    m_target = vec3(0,3*(2+sin(1.3*t))*100,0);

//    m_viewMat = glm::lookAt(m_camera, m_target, glm::vec3(0,1,0));
  //  m_projMat = glm::perspective(60.0,1.0, 1.0,1000.0);


    float c = m_time/10.0 ;
//    float beat =xm.GetVolume(6) + xm.GetVolume(7) + xm.GetVolume(9);
    float beat =xm.GetInstrument(9)*xm.GetVolume(9) + xm.GetFrequency(2)*0.5;
    for (auto v: m_physics.m_objects) {
        v->radius = (2+cos(c))*0.25;
        c = c+624.346;
        v->radius = 0.2;
        v->c1 = beat*10.0;
    }

//    m_objects[0]->m_uniforms["invVP"]->m_mat4 = glm::inverse(m_projMat*m_viewMat);
    m_objects[0]->m_uniforms["time"]->m_fval = m_time;
//    printf("%f\n",m_projMat[j][i]);


    r = 15;
/*    m_physics.Gravity2();
//    m_physics.ConstrainBox(vec3(0,r/2,0), vec3(r,r,r));

    m_physics.Move(0.01);
    */
    m_physics.ToArray(m_objects[0]->m_uniforms["spherePos"]->m_arr);

    float var1 = sin(m_time*2.34);
    float var2 = sin(m_time*1.23);
    SetForegroundColor(glm::vec3(1,1,1)*(rand()%100/100.0f));

//    float v = (rand()%100/100.0f);
    SetScreenColor(glm::vec3(1,1,1));

    m_targetObject->m_uniforms["chromatic"]->m_fval = 0.03;//0.03*sin(m_time/60.0);
//    m_targetObject->m_uniforms["chromatic"]->m_fval = 0.03;
}

