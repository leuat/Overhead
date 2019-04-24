#include "abstractscene.h"

AbstractScene::AbstractScene(int timer, int w, int h)
{
    m_timerEnd = timer;
    m_width = w;
    m_height = h;

}

AbstractScene::~AbstractScene() {
    for (auto v: m_objects)
        delete v;

    for (auto v: m_uniforms)
        delete v;
}

void AbstractScene::RegisterStandards(LGLObject* p1)
{
//    printf("%d\n",p1->m_programID);
    m_uniforms.push_back(new Uniform(p1->m_programID,"camera", Uniform::tVec3));
    m_uniforms.push_back(new Uniform(p1->m_programID,"target", Uniform::tVec3));

    m_uniforms.push_back(new Uniform(p1->m_programID,"invVP", Uniform::tMat4));
    m_uniforms.push_back(new Uniform(p1->m_programID,"time", Uniform::tScalar));
//    m_uniforms.push_back(new Uniform(p1->m_programID,"projMat", Uniform::tMat4));
  //  m_uniforms.push_back(new Uniform(p1->m_programID,"viewMat", Uniform::tMat4));

}

void AbstractScene::SetupFrameBuffer()
{
    glGenFramebuffers(1, &m_targetFramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, m_targetFramebufferName);

    glGenTextures(1, &m_renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, m_renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_width, m_height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    m_useFrameBuffer = true;


    m_targetObject = new LGLObject();
    m_targetObject->GenerateGenericPlane();
    vector<string>  inc;
    m_targetObject->Init("../resources/shaders/screen1.vert","../resources/shaders/screen1.frag", inc);

}




void AbstractScene::Init()
{
    SetupFrameBuffer();

}


void AbstractScene::Update(LXM& xm) {
    if (m_useFrameBuffer)
        glBindFramebuffer(GL_FRAMEBUFFER, m_targetFramebufferName);

    for (auto v : m_objects)
        v->Render();

    for (auto u: m_uniforms)
        u->SetUniform();

    if (m_useFrameBuffer) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        m_targetObject->Render();
    }

}
