//
// Created by springtom on 2020/4/30.
//

#include "LowPassEffect.h"
LowPassEffect::LowPassEffect(FilterParams *filterParams) {
    this->filterParams =filterParams;
}
LowPassEffect::~LowPassEffect() {

}
int LowPassEffect::initChild() {
    if(filterParams!=NULL){
        sox_effect_t *lowpass_effect = sox_create_effect(sox_find_effect("lowpass"));
        char *frequency = new char[10];
        char *width = new char[10];
        filterParams->getFrequency(&frequency);
        filterParams->getWidth(&width);
        char *args[] ={frequency,width};
        assert(sox_effect_options(lowpass_effect, 2, args) == SOX_SUCCESS);
        assert(sox_add_effect(chain, lowpass_effect, &signalInfo, &signalInfo) == SOX_SUCCESS);
        delete[] *args;
        delete lowpass_effect;
        LOGE("LowPassEffect::initChild2");
    }
    return SUCCESS;
}
