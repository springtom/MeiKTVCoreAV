//
// Created by springtom on 2020/4/24.
//

#include "EchoEffect.h"
EchoEffect::EchoEffect(EchoParams *echoParams) {
    this->echoParams =echoParams;
}
EchoEffect::~EchoEffect() {

}
int EchoEffect::initChild() {
    initChild(echoParams);
    return SUCCESS;
}
int EchoEffect::initChild(EchoParams *echoParams) {
    LOGE("EchoEffect::initChild");
    if(echoParams!=NULL){
        sox_effect_t *echoEffect = sox_create_effect(sox_find_effect("echo"));

        char *inputVolume = new char[10];
        echoParams->getInputVolume(&inputVolume);

        char *outputVolume = new char[10];
        echoParams->getOutputVolume(&outputVolume);

        char *delay = new char[10];
        echoParams->getDelay(&delay);

        char *attenuation = new char[10];
        echoParams->getAttenuation(&attenuation);

        char *args[] ={inputVolume,outputVolume,delay,attenuation};

        assert(sox_effect_options(echoEffect,4,args)==SOX_SUCCESS);
        assert(sox_add_effect(chain,echoEffect,&signalInfo,&signalInfo)==SOX_SUCCESS);
        delete[] *args;
        delete echoEffect;
        LOGE("EchoEffect::initChild2");
    }
    return SUCCESS;
}