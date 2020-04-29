//
// Created by springtom on 2020/4/23.
//

#ifndef MEIKTVCOREAV_SOXMANAGER_H
#define MEIKTVCOREAV_SOXMANAGER_H

#include <iostream>
#include  <list>
#include "SoxBaseEffect.h"
using namespace std;

class SoxManager {
private:
    SoxManager() {
        echoEffect = NULL;
        hasInit = false;
    }

    bool hasInit;
    list<SoxBaseEffect *> effects;

    SoxBaseEffect *echoEffect;




protected:

public:
    ~SoxManager() {
    }

    SoxManager(const SoxManager &) = delete;

    SoxManager &operator=(const SoxManager &) = delete;

    static SoxManager &getInstance() {
        static SoxManager instance;
        return instance;
    }

    int sampleRate;
    int channels;
    int bufferSize;

    virtual void initArgs(int sampleRate, int butterSize, int channels);

    virtual void addEffect(SoxBaseEffect *effect);

    virtual void setEchoEffect(SoxBaseEffect *effect);

    virtual void doProcess(short *audioSample, int size);

    virtual void destory();


};


#endif //MEIKTVCOREAV_SOXMANAGER_H
