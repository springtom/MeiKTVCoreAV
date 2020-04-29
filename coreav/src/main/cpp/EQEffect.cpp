//
// Created by springtom on 2020/4/23.
//

#include "EQEffect.h"

EQEffect::~EQEffect() {
}

EQEffect::EQEffect(list<EQParams *> *listEq) {
    this->listeQ = listEq;
}
int EQEffect::initChild(list<EQParams *> * eqparamslist) {
    if(NULL!=eqparamslist){
        list<EQParams*>::iterator ite;
        for(ite = eqparamslist->begin();ite!=eqparamslist->end();++ite){
            EQParams* eqParams = *ite;
            int frequency  = eqParams->getFrequency();
            if(frequency>signalInfo.rate/2){
                continue;
            }
            int eqArgSize = 3;
            char * frequencystr = new char[10];
            eqParams->getFrequency(&frequencystr);
            char * width  = new char[10];
            eqParams->getWidth(&width);
            char * gain = new char[10];
            eqParams->getGain(&gain);
            char * eqArgs[] = {frequencystr,width,gain};
            sox_effect_t * e = sox_create_effect(sox_find_effect("equalizer"));
            assert(sox_effect_options(e,eqArgSize,eqArgs)==SOX_SUCCESS);
            assert(sox_add_effect(chain,e,&signalInfo,&signalInfo)==SOX_SUCCESS);
            for (int i = 0; i < eqArgSize; ++i) {
                delete eqArgs[i];
            }
//            delete[]  *eqArgs;
           free(e);
        }
    }
    return SUCCESS;
}
int EQEffect::initChild() {
    LOGE("addEQ15.3.1");
    initChild(listeQ);
    LOGE("addEQ15.3.2");
    return SUCCESS;
}
