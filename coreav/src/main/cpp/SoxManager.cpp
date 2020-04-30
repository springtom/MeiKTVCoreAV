//
// Created by springtom on 2020/4/23.
//

#include "EQEffect.h"
#include "SoxManager.h"
#include "ReverbEffect.h"
#include "Log.h"

extern "C" {
#include "./sox.h"
}


void SoxManager::initArgs(int sampleRate, int butterSize, int channels) {
    LOGE("SoxManager initArgs1");
    sox_init();
    hasInit = true;
    LOGE("SoxManager initArgs2");
    SoxBaseEffect::outputSample = new short[butterSize * 2];
    this->sampleRate = sampleRate;
    this->bufferSize = butterSize;
    this->channels = channels;
    sox_globals.bufsiz = butterSize;
    LOGE("SoxManager initArgs3");
}

void SoxManager::addEffect(SoxBaseEffect *effect) {
    effects.push_back(effect);
}

void SoxManager::setEchoEffect(SoxBaseEffect *effect) {
    this->echoEffect = effect;
}


void SoxManager::doProcess(short *audioSample, int size) {
    LOGE("doProcess1");
    list<SoxBaseEffect *>::iterator ite;
    LOGE("doProcess2");
    for (ite = effects.begin(); ite != effects.end(); ++ite) {
        LOGE("doProcess3");
        SoxBaseEffect *effect = *ite;

        if (ReverbEffect *reverb = dynamic_cast<ReverbEffect *> (effect)) {
            LOGE("doProcess3.0");
            int len = sizeof(short) * size;
            short *wet = new short[len];
            short *echo = new short[len];

            LOGE("doProcess3.1");
            memcpy(wet, audioSample, len);
            memcpy(echo, audioSample, len);
            LOGE("doProcess3.2");
            if (echoEffect != NULL) {
                LOGE("doProcess3.3");
                echoEffect->process(echo, size);
                LOGE("doProcess3.4");
            }
            if (effect != NULL)
                effect->process(audioSample, size);
            LOGE("doProcess3.5");
            for (int i = 0; i < size; ++i) {
                audioSample[i] = (1-echoscale-wetscale) * audioSample[i] +wetscale * wet[i] + echoscale * echo[i];
            }
            LOGE("doProcess3.6");
            delete wet;
            delete echo;
        } else {
            LOGE("doProcess4");
            if (effect != NULL)
                effect->process(audioSample, size);
        }
    }
    LOGE("doProcess5");
}

void SoxManager::destory() {
    LOGE("destory1");
    list<SoxBaseEffect *>::iterator ite;
    LOGE("destory2");
    for (ite = effects.begin(); ite != effects.end(); ++ite) {
        LOGE("destory3");
        SoxBaseEffect *effect = *ite;
        LOGE("destory4");
        effect->destory();
        LOGE("destory5");
        delete (effect);
        LOGE("destory6");
    }
    if (hasInit) {
        sox_quit();
        hasInit = false;
    }
    LOGE("destory7");
    effects.clear();
    LOGE("destory8");
}