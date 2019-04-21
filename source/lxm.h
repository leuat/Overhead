#ifndef LXM_H
#define LXM_H
#include <math.h>

//#if defined(__cplusplus)
  extern "C" {                 // Make sure we have C-declarations in C++ programs
#include <xm.h>
  }
//#endif
#include <alsa/asoundlib.h>
#include "../resources/music/music.h"




class LXM
{
public:
    LXM();
    xm_context_t* ctx;
    snd_pcm_t* device;
    snd_pcm_hw_params_t* params;
    float buffer[4096];

    void gen_waveforms(void);
    void InitMusic();
    void Play();

};

#endif // LXM_H
