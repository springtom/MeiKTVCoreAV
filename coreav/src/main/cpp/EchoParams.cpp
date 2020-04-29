//
// Created by springtom on 2020/4/29.
//

#include "EchoParams.h"
#include <stdio.h>
EchoParams::EchoParams(float inputVolume, float outputVolume, int delay, float attenuation) {
    this->inputVolume = inputVolume;
    this->outputVolume = outputVolume;
    this->delay = delay;
    this->attenuation =attenuation;
}
EchoParams::~EchoParams() {

}

void EchoParams::getInputVolume(char **inputVolume) {
    sprintf(*inputVolume,"%f",this->inputVolume);
}
void EchoParams::getOutputVolume(char **outputVolume) {
    sprintf(*outputVolume,"%f",this->outputVolume);
}
void EchoParams::getDelay(char **delay) {
    sprintf(*delay,"%d",this->delay);
}
void EchoParams::getAttenuation(char **attenuation) {
    sprintf(*attenuation,"%f",this->attenuation);
}