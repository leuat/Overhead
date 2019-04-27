#include "abstractscene.h"

AbstractScene::AbstractScene(int timer, int w, int h)
{
    m_timerEnd = timer;    m_width = w;
    m_height = h;

}

AbstractScene::~AbstractScene() {
    for (auto v: m_objects)
        delete v;
}

void AbstractScene::SetForegroundColor(vec3 col)
{
    m_targetObject->m_uniforms["textColor"]->m_vec3 = col;
}

void AbstractScene::SetScreenColor(vec3 col)
{

    m_targetObject->m_uniforms["screenColor"]->m_vec3 = col;
}


void AbstractScene::RegisterStandards(LGLObject* p1)
{

    m_objects[0]->m_uniforms["camera"] = new Uniform(p1->m_programID,"camera", Uniform::tVec3);
    m_objects[0]->m_uniforms["target"] = new Uniform(p1->m_programID,"target", Uniform::tVec3);

    m_objects[0]->m_uniforms["invVP"]= new Uniform(p1->m_programID,"invVP", Uniform::tMat4);
    m_objects[0]->m_uniforms["time"]= new Uniform(p1->m_programID,"time", Uniform::tScalar);

}

void AbstractScene::InitFrameBufferOnly()
{
    glGenFramebuffers(1, &m_targetFramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, m_targetFramebufferName);


//    m_renderTexture.Init(m_width, m_height,0, "renderedTexture");

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


}

void AbstractScene::SetupFrameBuffer()
{
    InitFrameBufferOnly();

    m_targetObject = new LGLObject();
    m_targetObject->GenerateGenericPlane();
    vector<const char*>  inc;
//    m_targetObject->Init("../resources/shaders/screen1.vert","../resources/shaders/screen1.frag", inc);
    m_targetObject->Init(LShaders::screen1_vert,LShaders::screen1_frag, inc);

    m_targetObject->m_uniforms["textColor"]= new Uniform(m_targetObject->m_programID,"textColor",Uniform::tVec3);
    m_targetObject->m_uniforms["screenColor"] = new Uniform(m_targetObject->m_programID,"screenColor",Uniform::tVec3);
    m_targetObject->m_uniforms["chromatic"] = new Uniform(m_targetObject->m_programID,"chromatic",Uniform::tScalar);

    m_targetObject->m_uniforms["lamp"] = new Uniform(m_targetObject->m_programID,"lamp",Uniform::tScalar);
    m_targetObject->m_uniforms["lsca"] = new Uniform(m_targetObject->m_programID,"lsca",Uniform::tScalar);

    m_targetObject->m_uniforms["lamp"]->m_fval = 0.5;
    m_targetObject->m_uniforms["lsca"]->m_fval = 600;

//    m_targetObject->m_textures.push_back(&m_renderedTexture);
}




void AbstractScene::InitScene()
{

}


void AbstractScene::UpdateScene(LXM& xm, float dt) {
    m_time+=dt;
//    m_useFrameBuffer = false;
    if (m_useFrameBuffer)
        glBindFramebuffer(GL_FRAMEBUFFER, m_targetFramebufferName);

//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

     for (auto v : m_objects)
        v->Render();

    if (m_useFrameBuffer) {
        m_targetObject->UseProgram();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_renderedTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_frontTextureID);

        glUniform1i( glGetUniformLocation(m_targetObject->m_programID, "renderedTexture"), 0);
        glUniform1i( glGetUniformLocation(m_targetObject->m_programID, "frontTexture"), 1);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_targetObject->Render();

    }

}

void AbstractScene::CleanupScene() {}
