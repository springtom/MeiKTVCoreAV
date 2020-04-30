//
// Created by springtom on 2020/4/29.
//

#include "HighPassEffect.h"
HighPassEffect::HighPassEffect(FilterParams *filterParams) {
    this->filterParams =filterParams;
}
HighPassEffect::~HighPassEffect() {

}
int HighPassEffect::initChild() {
    if(filterParams!=NULL){
        sox_effect_t *highpass_effect = sox_create_effect(sox_find_effect("highpass"));
        char *frequency = new char[10];
        char *width = new char[10];
        filterParams->getFrequency(&frequency);
        filterParams->getWidth(&width);
        char *args[] ={frequency,width};
        assert(sox_effect_options(highpass_effect,2,args)==SOX_SUCCESS);
        assert(sox_add_effect(chain,highpass_effect,&signalInfo,&signalInfo)==SOX_SUCCESS);
        delete[] *args;
        delete highpass_effect;
        LOGE("HighPassEffect::initChild2");
    }
    return SUCCESS;
}


