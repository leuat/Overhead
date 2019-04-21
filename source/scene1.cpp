#include "Scene1.h"



void Scene1::Init()
{
   LGLObject* p1 = new LGLObject();
   p1->GenerateGenericPlane();
   p1->Init("../resources/shaders/scene1.vert","../resources/shaders/scene1.frag");
   m_objects.push_back(p1);


    RegisterStandards(p1);
//   m_projMat = getProjectionMatrix();
  // m_viewMat = getViewMatrix();

}

void Scene1::Update()
{
    AbstractScene::Update();

    m_uniforms[0]->m_vec3 = m_camera;
    m_uniforms[1]->m_vec3 = m_target;

    m_target = vec3(0,0,0);


    float r = 10;
    float t = m_time/10 ;
    m_camera  = glm::vec3(cos(t)*r,0,sin(t)*r);

    m_viewMat = glm::lookAt(m_camera, m_target, glm::vec3(0,1,0));
//    m_projMat = glm::perspective(70,1,1,1000);
    m_projMat = glm::perspective(60.0,640/480.0, 1.0,1000.0);

//    m_uniforms[2]->m_mat4 = m_projMat;
  //  m_uniforms[3]->m_mat4 = m_viewMat;


    m_uniforms[2]->m_mat4 = glm::inverse(m_projMat*m_viewMat);
//    printf("%f\n",m_projMat[j][i]);

    m_time++;
}
