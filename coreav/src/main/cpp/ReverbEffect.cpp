//
// Created by springtom on 2020/4/24.
//


#include <cstring>
#include <stdlib.h>
#include "ReverbEffect.h"

ReverbEffect::ReverbEffect(ReverbParams *reverbParams) {
    this->reverbParams = reverbParams;
}
ReverbEffect::~ReverbEffect() {

}

int ReverbEffect::initChild() {
    initChild(reverbParams);
    return SUCCESS;
}
int ReverbEffect::initChild(ReverbParams* reverbParams) {
    if(NULL==reverbParams)
        return ERROR;
    int argsSize = 7;

    char *wetOnly = new char[10];
    reverbParams->getWetOnly(&wetOnly);

    char *reverbrance = new char[10];
    reverbParams->getReverbrance(&reverbrance);

    char *damping = new char[10];
    reverbParams->getDamping(&damping);

    char *roomScale = new char[10];
    reverbParams->getRoomScale(&roomScale);

    char *stereoDepth = new char[10];
    reverbParams->getStereoDepth(&stereoDepth);

    char *preDelay = new char[10];
    reverbParams->getPreDelay(&preDelay);

    char *wetGain = new char[10];
    reverbParams->getWetGain(&wetGain);

    char * reverbArgs[] = {wetOnly,reverbrance,damping,roomScale,stereoDepth,preDelay,wetGain};

    sox_effect_t * e = sox_create_effect(sox_find_effect("reverb"));
    assert(sox_effect_options(e,argsSize,reverbArgs)==SOX_SUCCESS);
    assert(sox_add_effect(chain,e,&signalInfo,&signalInfo)==SOX_SUCCESS);
    free(e);
    return SUCCESS;
}

