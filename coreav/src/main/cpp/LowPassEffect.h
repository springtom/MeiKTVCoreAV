//
// Created by springtom on 2020/4/30.
//

#ifndef MEIKTVCOREAV_LOWPASSEFFECT_H
#define MEIKTVCOREAV_LOWPASSEFFECT_H


#include "SoxBaseEffect.h"
#include "FilterParams.h"

class LowPassEffect : public SoxBaseEffect{
private:
    FilterParams* filterParams;

    virtual int initChild();



public:
    LowPassEffect(FilterParams * filterParams);
    ~LowPassEffect();
};


#endif //MEIKTVCOREAV_LOWPASSEFFECT_H
