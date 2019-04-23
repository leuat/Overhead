#include "Scene1.h"



void Scene1::Init()
{
   LGLObject* p1 = new LGLObject();
   p1->GenerateGenericPlane();
   vector<string> includes;
   includes.push_back("../resources/shaders/raymarcherinc.frag");
   p1->Init("../resources/shaders/scene1.vert","../resources/shaders/scene1.frag", includes);
   m_objects.push_back(p1);


    RegisterStandards(p1);
    float r= 10;
    m_physics.InitRandom(m_noSpheres,vec3(r,r,r),vec3(r/2,0,r/2));
/*    for (int i=0;i<m_noSpheres;i++) {
        m_sPos.push_back(0.3*vec3(rand()%r-r/2,rand()%r,rand()%r-r/2));
    }
*/
    m_uniforms.push_back(new Uniform(p1->m_programID,"spherePos",m_noSpheres*5));

//   m_projMat = getProjectionMatrix();
  // m_viewMat = getViewMatrix();

}

void Scene1::Update(LXM& xm)
{
    AbstractScene::Update(xm);

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
    m_physics.ConstrainBox(vec3(0,r/2,0), vec3(r,r,r));

    m_physics.Move(0.01);
            m_physics.ToArray(m_uniforms[4]->m_arr);


    m_time++;
}
