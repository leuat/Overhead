#ifndef LPHYSICS_H
#define LPHYSICS_H

#include <source/engine/lglobject.h>

class LPhysicsObject {
public:
    LPhysicsObject(vec3 p) {
        P = p;
        c1 = (rand()%10000)/10000.0;
        radius= 0.25;
        float s= 0.3;
        V.x = ((rand()%10000/10000.0)-0.5)*s;
        V.z = ((rand()%10000/10000.0)-0.5)*s;
        V.y = ((rand()%10000/10000.0)-0.5)*s;
    }
    vec3 P,V,A;
    vec3 col;
    float c1;
    float radius;
    float mass = 1;
    void Move(float dt) {
        P=P+V;
        V=V+A*dt;
        A = vec3(0,0,0);
    }

    void ApplyForce(vec3 F) {
        A+=F;
    }

    void Gravity(LPhysicsObject* o) {
        vec3 dd = o->P - P;
        float d = length(dd);
        dd = normalize(dd);
        float F = 1*mass*o->mass/pow(d+0.5,2.0);
//        printf("%f\n",dd.x);
        ApplyForce(F*dd);
        o->ApplyForce(-F*dd);
    }
};


class LPhysics
{
public:
    vector<LPhysicsObject*> m_objects;

    void InitRandom(int N, vec3 spread, vec3 center);

    void Gravity2();

    void Move(float dt) {
        for (LPhysicsObject* l : m_objects)
            l->Move(dt);
    }

    void ConstrainBox(vec3 center, vec3 size);

    void ToArray(float* arr);

public:
    LPhysics();
};

#endif // LPHYSICS_H
