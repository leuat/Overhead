#include <source/lglwrap.h>
#include <source/lxm.h>

#include <source/Scene1.h>
#include <source/Scenes/sceneplanet.h>
#define GLEW_STATIC



int main( void )
{
    // Initialise GLFW
    LXM xm;

    xm.InitMusic();
    LGLWrap app(&xm);
 //   int w = 800;
   // int h= 600;
    int w = 1600;
    int h= 1024;

    app.m_scenes.push_back(new ScenePlanet(200,w,h));
    app.m_scenes.push_back(new Scene1(2000,w,h));
    app.Init(w,h);
    return app.Exec();
}
