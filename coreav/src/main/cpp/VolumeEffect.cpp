//
// Created by springtom on 2020/4/30.
//

#include "VolumeEffect.h"
VolumeEffect::VolumeEffect(int addVolume) {
this->addVolume = addVolume;
}
int VolumeEffect::initChild() {
    sox_effect_t *vol_effect = sox_create_effect(sox_find_effect("vol"));
    char *vol = new char[10];
    getAddVolume(&vol);
    char *args[] ={vol};
    assert(sox_effect_options(vol_effect, 1, args) == SOX_SUCCESS);
    assert(sox_add_effect(chain, vol_effect, &signalInfo, &signalInfo) == SOX_SUCCESS);
    delete[] *args;
    delete vol_effect;
    LOGE("LowPassEffect::initChild2");
    return SUCCESS;
}

void VolumeEffect::getAddVolume(char **addVolume) {
    sprintf(*addVolume,"%d",this->addVolume);
}