//
// Created by springtom on 2020/4/23.
//

#ifndef MEIKTVCOREAV_SOXBASEEFFECT_H
#define MEIKTVCOREAV_SOXBASEEFFECT_H

#define  SUCCESS 1
#define ERROR -1;

#include "math.h"
#include "Log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern "C"{
#include "./sox.h"
};


class SoxBaseEffect{
private:
    virtual void initSignal();
    virtual void initEncoding();
protected:
    sox_signalinfo_t signalInfo;
    sox_encodinginfo_t encodingInfo;
    virtual int initchinaStart();
    virtual int initchinaEnd();
    virtual int initChild();
    virtual int initsuper();

public:
    SoxBaseEffect();
    ~SoxBaseEffect();

    // 这三个静态有点呕心，破坏了类结构，子类公用，多线程处理子类会有问题。这块儿正常处理数据是单线程，应该没有问题。
    static short* intputSample;
    static int size;
    static short* outputSample;

    sox_effects_chain_t * chain;
    virtual int process(short*audioSample,int size);

    virtual int init(){
        LOGE("addEffect15.1");
        initsuper();
        LOGE("addEffect15,2");
        initchinaStart();
        LOGE("addEffect15.3");
        initChild();
        LOGE("addEffect15.4");
        initchinaEnd();
        LOGE("addEffect15.5");
        return SUCCESS;
    }
    virtual void destory();
};





#endif //MEIKTVCOREAV_SOXBASEEFFECT_H
