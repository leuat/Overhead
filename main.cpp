#include <source/lglwrap.h>
#include <source/lxm.h>

#include <source/Scene1.h>

int main( void )
{
    // Initialise GLFW
    LXM xm;
    xm.InitMusic();
    LGLWrap app(&xm);
    int w = 800;
    int h= 600;
    app.m_scenes.push_back(new Scene1(2000,w,h));
    app.Init(800,600);

    return app.Exec();
}
