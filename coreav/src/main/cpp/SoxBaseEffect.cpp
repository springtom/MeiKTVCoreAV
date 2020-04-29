//
// Created by springtom on 2020/4/23.
//

#include "SoxBaseEffect.h"
#include "SoxManager.h"

short *SoxBaseEffect::intputSample = NULL;
int SoxBaseEffect::size = 0;
short *SoxBaseEffect::outputSample = NULL;

SoxBaseEffect::SoxBaseEffect() {
    chain = NULL;
}


SoxBaseEffect::~SoxBaseEffect() {

}

int SoxBaseEffect::initChild() {
    LOGE("addEQ15.3.SoxBaseEffect");
}


static int inputDrainCallBack(sox_effect_t *effp, sox_sample_t *obuf, size_t *osamp) {
    *osamp = SoxBaseEffect::size;
    for (int i = 0; i < *osamp; i++) {
        obuf[i] = ((sox_sample_t) (SoxBaseEffect::intputSample[i]) << 16);
    }
    return SOX_SUCCESS;
}

static int outputFlowCallBack(sox_effect_t *effp LSX_UNUSED, sox_sample_t const *ibuf,
                              sox_sample_t *obuf LSX_UNUSED, size_t *isamp, size_t *osamp) {
    if (*isamp) {
        for (int i = 0; i < *isamp; i++) {

            SoxBaseEffect::outputSample[i] = (short) (ibuf[i] >> 16);
        }
    }
    *osamp = 0;
    return *isamp == 0 ? SOX_SUCCESS : SOX_EOF;
}

static sox_effect_handler_t const *inputHandler() {
    static sox_effect_handler_t handler = {
            "input",
            NULL,
            SOX_EFF_MCHAN | SOX_EFF_MODIFY,
            NULL,
            NULL,
            NULL,
            inputDrainCallBack,
            NULL,
            NULL,
            0
    };
    return &handler;
}

static sox_effect_handler_t const *outputHandler() {
    static sox_effect_handler_t handler = {
            "output",
            NULL,
            SOX_EFF_MCHAN | SOX_EFF_MODIFY | SOX_EFF_PREC,
            NULL,
            NULL,
            outputFlowCallBack,
            NULL,
            NULL,
            NULL,
            0
    };
    return &handler;
}


void SoxBaseEffect::initSignal() {
    signalInfo.precision = 16;
    signalInfo.channels = SoxManager::getInstance().channels;
    signalInfo.rate = SoxManager::getInstance().sampleRate;
    signalInfo.mult = NULL;
}

void SoxBaseEffect::initEncoding() {
    encodingInfo.encoding = (sox_encoding_t) 1;
    encodingInfo.bits_per_sample = 16;
    encodingInfo.reverse_bytes = (sox_option_t) 0;
    encodingInfo.reverse_nibbles = (sox_option_t) 0;
    encodingInfo.reverse_bits = (sox_option_t) 0;
    encodingInfo.compression = INFINITY;
    encodingInfo.opposite_endian = (sox_bool) 0;
}


int SoxBaseEffect::initsuper() {
    initSignal();
    initEncoding();
    return SUCCESS;
}

int SoxBaseEffect::initchinaStart() {
    LOGE("initchinaStart1");
    chain = sox_create_effects_chain(&encodingInfo, &encodingInfo);
    LOGE("initchinaStart2");
    sox_effect_t *e = sox_create_effect(inputHandler());
    LOGE("initchinaStart3");
    assert(sox_add_effect(chain, e, &signalInfo, &signalInfo) == SOX_SUCCESS);
    LOGE("initchinaStart4");
    free(e);
    LOGE("initchinaStart5");
    return SUCCESS;
}


int SoxBaseEffect::initchinaEnd() {
    sox_effect_t *e = sox_create_effect(outputHandler());
    assert(sox_add_effect(chain, e, &signalInfo, &signalInfo) == SOX_SUCCESS);
    return SUCCESS;
}

int SoxBaseEffect::process(short *audioSample, int size) {
    SoxBaseEffect::size = size;
    SoxBaseEffect::intputSample = audioSample;
    sox_flow_effects(chain, NULL, NULL);
    memcpy(audioSample, SoxBaseEffect::outputSample, size * (sizeof(short)));
    return SoxBaseEffect::size;
}


void SoxBaseEffect::destory() {

    if (NULL != chain) {
        sox_delete_effects_chain(chain);
        LOGE("soxBaseEffect destory1")
        chain = NULL;
    }

    if (NULL != intputSample) {
        delete intputSample;
        intputSample = NULL;
    }

    if (NULL != outputSample) {
        delete outputSample;
        outputSample = NULL;
    }
}




