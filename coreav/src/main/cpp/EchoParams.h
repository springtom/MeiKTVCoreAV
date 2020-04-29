//
// Created by springtom on 2020/4/29.
//

#ifndef MEIKTVCOREAV_ECHOPARAMS_H
#define MEIKTVCOREAV_ECHOPARAMS_H


class EchoParams {
private:
    float inputVolume;
    float outputVolume;
    int delay;
    float attenuation;
public:
    EchoParams(float inputVolume, float outputVolume,int delay, float attenuation);
    ~EchoParams();
    void getInputVolume(char **inputVolume);
    void getOutputVolume(char **outputVolume);
    void getDelay(char** delay);
    void getAttenuation(char ** attenuation);
};


#endif //MEIKTVCOREAV_ECHOPARAMS_H
