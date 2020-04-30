//
// Created by springtom on 2020/4/30.
//

#ifndef MEIKTVCOREAV_VOLUMEEFFECT_H
#define MEIKTVCOREAV_VOLUMEEFFECT_H


#include "SoxBaseEffect.h"

class VolumeEffect: public SoxBaseEffect {
private:
    int addVolume;
    virtual int initChild();
    virtual void getAddVolume(char** addVolume);
public:
    VolumeEffect(int addVolume);
    ~VolumeEffect();
};


#endif //MEIKTVCOREAV_VOLUMEEFFECT_H
