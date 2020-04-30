//
// Created by springtom on 2020/4/24.
//

#include "EQParams.h"
#include <stdio.h>
EQParams::EQParams(int frequency, float width, int gain) {
    this->frequency = frequency;
    this->width = width;
    this->gain = gain;
}
EQParams::~EQParams() {
}
void EQParams::getFrequency(char **frequency) {
 sprintf(*frequency,"%d",this->frequency);
}
void EQParams::getWidth(char **width) {
    sprintf(*width,"%fq",this->width);
}
void EQParams::getGain(char **gain) {
    sprintf(*gain,"%d",this->gain);
}