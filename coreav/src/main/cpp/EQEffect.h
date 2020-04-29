//
// Created by springtom on 2020/4/23.
//

#ifndef MEIKTVCOREAV_EQEFFECT_H
#define MEIKTVCOREAV_EQEFFECT_H


#include <list>
#include "SoxBaseEffect.h"
#include "EQParams.h"
using namespace std;

class EQEffect: public SoxBaseEffect {

protected:
    list<EQParams*> * listeQ;
    virtual int initChild(list<EQParams*> * listEq);
    virtual int initChild();
public:
    EQEffect(list<EQParams*> * listEq);
    ~EQEffect();
};


#endif //MEIKTVCOREAV_EQEFFECT_H
