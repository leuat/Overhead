#ifndef LXM_H
#define LXM_H
#include <math.h>

//#if defined(__cplusplus)
  extern "C" {                 // Make sure we have C-declarations in C++ programs
#include <xm.h>
  }
//#endif
#ifdef __linux__
#include <alsa/asoundlib.h>
#endif

namespace LMusic {
    extern char music[];
}

#ifdef _WIN32
//#include "source/cwavebuffer.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

#endif


class LXM
{
public:
    LXM();
    xm_context_t* ctx;
#ifdef __linux__
    snd_pcm_t* device;
    snd_pcm_hw_params_t* params;
#endif
#ifdef _WIN32
//    CWaveOut* m_cwb;
#endif
    float buffer[4096];
    void gen_waveforms(void);
    void InitMusic();
    void Play();
    void Terminate();

    float GetFrequency(int channel) {
        return xm_get_frequency_of_channel(ctx,channel);
    }

    float GetVolume(int channel) {
        return xm_get_volume_of_channel(ctx,channel);
    }

    float GetInstrument(int channel) {
        return xm_get_instrument_of_channel(ctx, channel);
    }

};

#endif // LXM_H
