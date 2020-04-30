//
// Created by springtom on 2020/4/30.
//

#include "FilterParams.h"
#include <stdio.h>
FilterParams::FilterParams(int frequency) {
    this->frequency = frequency;
}
FilterParams::~FilterParams() {
}
void FilterParams::getFrequency(char **frequency) {
    sprintf(*frequency,"%d",this->frequency);
}

void FilterParams::getWidth(char **width) {
    sprintf(*width,"0.2q");
}
