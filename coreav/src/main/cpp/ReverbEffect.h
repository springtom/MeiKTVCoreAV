//
// Created by springtom on 2020/4/24.
//

#ifndef MEIKTVCOREAV_REVERBEFFECT_H
#define MEIKTVCOREAV_REVERBEFFECT_H

#include "ReverbParams.h"
#include "SoxBaseEffect.h"


class ReverbEffect: public SoxBaseEffect{
protected:
    int initChild();
    ReverbParams * reverbParams;

public:
    ReverbEffect(ReverbParams * reverbParams);
    ~ReverbEffect();
};


#endif //MEIKTVCOREAV_REVERBEFFECT_H
