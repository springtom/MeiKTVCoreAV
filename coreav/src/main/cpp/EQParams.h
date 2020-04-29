//
// Created by springtom on 2020/4/24.
//

#ifndef MEIKTVCOREAV_EQPARAMS_H
#define MEIKTVCOREAV_EQPARAMS_H


class EQParams {
private:
    int frequency;
    float width;
    int gain;
public:
    EQParams(int frequency, float width,int gain);
    virtual ~EQParams();
    virtual void getFrequency(char** frequceny);
    virtual void getWidth(char** width);
    virtual void getGain(char** gain);
    int getFrequency(){
        return frequency;
    }
};


#endif //MEIKTVCOREAV_EQPARAMS_H
