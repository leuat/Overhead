#include "lxm.h"

LXM::LXM()
{

}

void LXM::gen_waveforms() {
    size_t i;
    int8_t* buf;
    size_t len;
    uint8_t bits;

    /* Square, large duty, half volume */
    buf = (int8_t*)xm_get_sample_waveform(ctx, 1, 0, &len, &bits);
    for(i = 0x40; i < len; ++i) buf[i] = 127;

    /* Ramp */
    buf = (int8_t*)xm_get_sample_waveform(ctx, 2, 0, &len, &bits);
    for(i = 0; i < len; ++i) buf[i] = (256 *sin(i/10.0)) / len - 128;

    /* Square, small duty */
    buf = (int8_t*)xm_get_sample_waveform(ctx, 4, 0, &len, &bits);
    for(i = 0; i < 0x80; ++i) buf[i] = -128;
    for(; i < 0xB0; ++i) buf[i] = 127;
    for(; i < len; ++i) buf[i] = -128;

    /* XXX: Kick */
    /* XXX: Pad */
    /* XXX: Drum */

    /* Noise */
    buf = (int8_t*)xm_get_sample_waveform(ctx, 8, 0, &len, &bits);
    unsigned int next = 1;
    for(i = 0; i < len; ++i) {
        next = next * 8127 + 1; /* A very simple linear congruence generator, see rand(3) */
        buf[i] = next >> 16 & 0xFF;
    }
}

void LXM::InitMusic() {
    unsigned int rate = 48000;

    snd_pcm_open(&device, "default", SND_PCM_STREAM_PLAYBACK, 0);
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(device, params);
    snd_pcm_hw_params_set_access(device, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(device, params, SND_PCM_FORMAT_FLOAT);
    snd_pcm_hw_params_set_channels(device, params, 2);
    snd_pcm_hw_params_set_rate_near(device, params, &rate, NULL);
    snd_pcm_hw_params(device, params);

 //           xm_create_context_from_libxmize(&ctx, music, rate);
    xm_create_context(&ctx, music, rate);
    //        gen_waveforms();

    snd_pcm_prepare(device);

}

void LXM::Play()
{
   xm_generate_samples(ctx, buffer, 2048);
   snd_pcm_writei(device, buffer, 2048);

}


