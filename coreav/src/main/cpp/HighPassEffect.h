//
// Created by springtom on 2020/4/29.
//

#ifndef MEIKTVCOREAV_HIGHPASSEFFECT_H
#define MEIKTVCOREAV_HIGHPASSEFFECT_H


#include "SoxBaseEffect.h"
#include "FilterParams.h"

class HighPassEffect: public SoxBaseEffect {
private:
    FilterParams* filterParams;

    virtual int initChild();


public:
    HighPassEffect(FilterParams * filterParams);
    ~HighPassEffect();
};


#endif //MEIKTVCOREAV_HIGHPASSEFFECT_H
