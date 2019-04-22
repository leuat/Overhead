#include "lphysics.h"

void LPhysics::InitRandom(int N, vec3 spread, vec3 center)
{
    m_objects.clear();
    for (int i=0;i<N;i++) {
        int max = 40000;
        m_objects.push_back(new LPhysicsObject(vec3(
                                spread.x*((rand()%max)/(float)max) - center.x,
                                spread.y*((rand()%max)/(float)max) - center.y,
                                spread.z*((rand()%max)/(float)max) - center.z
                                )));
    }
}

void LPhysics::Gravity2()
{
#pragma omp paralell for
    for (int i=0;i<m_objects.size()-1;i++)
        for (int j=i+1;j<m_objects.size();j++) {
            if (m_objects[i]!=m_objects[j])
            m_objects[i]->Gravity(m_objects[j]);
        }
}

void LPhysics::ConstrainBox(vec3 center, vec3 size)
{
    float delta = 0.01;
    for (auto v: m_objects) {
        if (v->P.x>center.x+size.x) {
            v->V.x = -v->V.x;
            v->P.x = center.x+size.x-delta;
        }
        if (v->P.x<center.x-size.x) {
            v->V.x = -v->V.x;
            v->P.x = center.x-size.x+delta;
        }

        if (v->P.y>center.y+size.y) {
            v->V.y = -v->V.y;
            v->P.y = center.y+size.y-delta;
        }
        if (v->P.y<center.y-size.y) {
            v->V.y = -v->V.y;
            v->P.y = center.y-size.y+delta;
        }

        if (v->P.z>center.z+size.z) {
            v->V.z = -v->V.z;
            v->P.z = center.z+size.z-delta;
        }
        if (v->P.z<center.z-size.z) {
            v->V.z = -v->V.z;
            v->P.z = center.z-size.z+delta;
        }

    }

}

void LPhysics::ToArray(float *arr)
{
    for (int i=0;i<m_objects.size();i++) {
//        printf("%f\n",m_objects[i]->P.y);
        arr[5*i+0] = m_objects[i]->P.x;
        arr[5*i+1] = m_objects[i]->P.y;
        arr[5*i+2] = m_objects[i]->P.z;
        arr[5*i+3] = m_objects[i]->c1;
        arr[5*i+4] = m_objects[i]->radius;
    }
}

LPhysics::LPhysics()
{

}
