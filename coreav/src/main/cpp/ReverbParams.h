//
// Created by springtom on 2020/4/24.
//

#ifndef MEIKTVCOREAV_REVERBPARAMS_H
#define MEIKTVCOREAV_REVERBPARAMS_H

#include <stdio.h>


class ReverbParams {
protected:
    int reverberance;
    int damping;
    int roomScale;
    int stereoDepth;
    int preDelay;
    int wetGain;
public:
    ReverbParams(int reverberance,int damping,int roomScale,int stereoDepth,int preDelay,int wetGain);
    ~ReverbParams();

    virtual void getWetOnly(char** wetOnly);
    virtual void getReverbrance(char** reverbrance);
    virtual void getDamping(char** damping);
    virtual void getRoomScale(char** roomScale);
    virtual void getStereoDepth(char ** stereoDepth);
    virtual void getPreDelay(char** preDelay);
    virtual void getWetGain(char** wetGain);
};


#endif //MEIKTVCOREAV_REVERBPARAMS_H
