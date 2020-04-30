//
// Created by springtom on 2020/4/30.
//

#ifndef MEIKTVCOREAV_FILTERPARAMS_H
#define MEIKTVCOREAV_FILTERPARAMS_H


class FilterParams {
private:
    int frequency;
public:
    FilterParams(int frequency);
    ~FilterParams();
    virtual void getFrequency(char** frequency);

    virtual void getWidth(char** width);
};


#endif //MEIKTVCOREAV_FILTERPARAMS_H
