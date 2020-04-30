//
// Created by springtom on 2020/4/24.
//

#ifndef MEIKTVCOREAV_ECHOEFFECT_H
#define MEIKTVCOREAV_ECHOEFFECT_H


#include "SoxBaseEffect.h"
#include "EchoParams.h"

class EchoEffect: public SoxBaseEffect {
private:
    EchoParams* echoParams;

    virtual int initChild();

public:
    EchoEffect(EchoParams * echoParams);
    ~EchoEffect();
};


#endif //MEIKTVCOREAV_ECHOEFFECT_H
