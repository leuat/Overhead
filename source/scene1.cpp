#include "Scene1.h"



void Scene1::InitScene()
{
    AbstractScene::InitScene();

   LGLObject* p1 = new LGLObject();
   p1->GenerateGenericPlane();
   vector<const char*> includes;
   includes.push_back(raymarcherinc);
//   p1->Init("../resources/shaders/scene1.vert","../resources/shaders/scene1.frag", includes);
   p1->Init(scene1_vert,scene1_frag, includes);

   m_objects.push_back(p1);

//   printf("WOOOT\n");
  // printf("SIZE : %d\n", sizeof(arcadeclassic));
    m_fr.Init(allerta, sizeof(allerta),64, m_width, m_height);

    m_fr.InitFrameBufferOnly();
    m_fr.RenderText("PROXIMA",0.1,0.4,0.003f,0.006f,vec3(1,1,1));

    m_frontTextureID =  m_fr.m_renderedTexture;


//    m_frontTextureID =  m_fr.m_characters[5].TextureID;//   m_fr.m_renderedTexture;
//    m_frontTextureID =  m_fr.m_renderedTexture;

    RegisterStandards(p1);
    float r= 10;
    m_physics.InitRandom(m_noSpheres,vec3(r,r,r),vec3(r/2,0,r/2));
    m_uniforms.push_back(new Uniform(p1->m_programID,"spherePos",m_noSpheres*5));



   //m_projMat = getProjectionMatrix();
  // m_viewMat = getViewMatrix();
    SetupFrameBuffer();
}

void Scene1::UpdateScene(LXM& xm)
{
    AbstractScene::UpdateScene(xm);

    m_uniforms[0]->m_vec3 = m_camera;
    m_uniforms[1]->m_vec3 = m_target;

    float r = 6;
    float t = m_time/60.0 ;
    m_camera  = glm::vec3(cos(t)*r,0.5*(cos(t*0.3)*r + r*1.3),sin(t)*r);
    m_target = vec3(0,3*(2+sin(1.3*t)),0);

    m_viewMat = glm::lookAt(m_camera, m_target, glm::vec3(0,1,0));
//    m_projMat = glm::perspective(70,1,1,1000);
//    m_projMat = glm::perspective(cos(0.5*t)*20 + 80.0,1.0, 1.0,1000.0);
    m_projMat = glm::perspective(60.0,1.0, 1.0,1000.0);

//    m_uniforms[2]->m_mat4 = m_projMat;
  //  m_uniforms[3]->m_mat4 = m_viewMat;

    float c = m_time/10.0 ;
//    float beat =xm.GetVolume(6) + xm.GetVolume(7) + xm.GetVolume(9);
    float beat =xm.GetInstrument(9)*xm.GetVolume(9) + xm.GetFrequency(2)*0.5;
    for (auto v: m_physics.m_objects) {
        v->radius = (2+cos(c))*0.25;
        c = c+624.346;
        v->radius = 0.2;
        v->c1 = beat*10.0;
    }

    m_uniforms[2]->m_mat4 = glm::inverse(m_projMat*m_viewMat);
    m_uniforms[3]->m_fval = m_time;
//    printf("%f\n",m_projMat[j][i]);


    r = 15;
    m_physics.Gravity2();
//    m_physics.ConstrainBox(vec3(0,r/2,0), vec3(r,r,r));

    m_physics.Move(0.01);
            m_physics.ToArray(m_uniforms[4]->m_arr);

    float var1 = sin(m_time*2.34);
    float var2 = sin(m_time*1.23);
    SetForegroundColor(glm::vec3(1,1,1)*(rand()%100/100.0f));


    m_time++;
}

