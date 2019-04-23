#include <source/lglwrap.h>
#include <source/lxm.h>

#include <source/Scene1.h>

int main( void )
{
    // Initialise GLFW
    LXM xm;
    xm.InitMusic();
    LGLWrap app(&xm);
    app.m_scenes.push_back(new Scene1(2000));
    app.Init(800,600);

    return app.Exec();
}
