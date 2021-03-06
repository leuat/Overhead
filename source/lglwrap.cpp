#include "lglwrap.h"
#include <time.h>
LGLWrap::LGLWrap(LXM* lxm)
{
    m_lxm = lxm;
}

int LGLWrap::Init(int w, int h)
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
//        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Open a window and create its OpenGL context
    m_window = glfwCreateWindow( w, h, "", NULL, NULL);
#ifdef IS_DEBUG
    if( m_window == NULL ){
        printf("Failed to create GLFW window\n");
    //    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
      //  getchar();
        glfwTerminate();
        return -1;
    }
#endif
    glfwMakeContextCurrent(m_window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
#ifdef IS_DEBUG
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
#endif
        glfwTerminate();
        return -1;
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}



int LGLWrap::Exec()
{
    if (m_scenes.size()!=0) {
        m_currentScene = m_scenes[0];
     m_currentScene->InitScene();}
     int m_curSceneIdx = 0;
    bool done = false;
    m_lxm->Play();
    m_timer = 0;
    float prev = clock();
    int tt;
//    const clock_t begin_time = clock();

    do{

        float k = clock();
        m_lxm->Play();
        float playt = (clock () - prev ) /  CLOCKS_PER_SEC;
  //      printf("Time: %f\n",playt );

        float dt = (clock () - prev ) /  CLOCKS_PER_SEC*1000.0;
        if (dt<0.01) dt = 0.01f;
        prev = clock();
//        printf("%f\n",dt);
        glClear( GL_COLOR_BUFFER_BIT );

//        printf("FPS: %f\n",(1.0/(dt/1000.0)) );


        if (m_currentScene!=nullptr) {
        m_currentScene->UpdateScene(*m_lxm,dt);

        if (m_timer>m_currentScene->m_timerEnd) {
            m_curSceneIdx++;
            if (m_curSceneIdx>=m_scenes.size())
                done = true;
            else {
                m_currentScene->CleanupScene();
                m_currentScene = m_scenes[m_curSceneIdx];
                m_currentScene->InitScene();

            }
        }
        }
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        m_timer+=dt;

    } // Check if the ESC key was pressed or the window was closed
    while ( glfwGetKey(m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(m_window) == 0  && !done);
    // Cleanup VBO

    // Close OpenGL window and terminate GLFW

    glfwTerminate();
    m_lxm->Terminate();
    return 0;
}
