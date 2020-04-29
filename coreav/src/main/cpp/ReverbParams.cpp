//
// Created by springtom on 2020/4/24.
//

#include "ReverbParams.h"
ReverbParams::ReverbParams(int reverberance, int damping, int roomScale, int stereoDepth,
                           int preDelay, int wetGain) {
    this->reverberance = reverberance;
    this->damping = damping;
    this->roomScale = roomScale;
    this->stereoDepth = stereoDepth;
    this->preDelay = preDelay;
    this->wetGain = wetGain;
}
ReverbParams::~ReverbParams() {

}
void ReverbParams::getWetOnly(char **wetOnly) {
    sprintf(*wetOnly,"%s","-w");
}
void ReverbParams::getReverbrance(char **reverbrance) {
    sprintf(*reverbrance,"%d",this->reverberance);
}
void ReverbParams::getDamping(char **damping) {
    sprintf(*damping,"%d",this->damping);
}
void ReverbParams::getRoomScale(char **roomScale) {
    sprintf(*roomScale,"%d",this->roomScale);
}
void ReverbParams::getStereoDepth(char **stereoDepth) {
    sprintf(*stereoDepth,"%d",this->stereoDepth);
}
void ReverbParams::getPreDelay(char **preDelay) {
    sprintf(*preDelay,"%d",this->preDelay);
}
void ReverbParams::getWetGain(char **wetGain) {
    sprintf(*wetGain,"%d",this->wetGain);
}
