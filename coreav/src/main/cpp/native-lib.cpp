#include <jni.h>
#include <string>
#include "Log.h"
#include "SoxManager.h"
#include "SoxBaseEffect.h"
#include "EQParams.h"
#include "EQEffect.h"
#include "ReverbParams.h"
#include "ReverbEffect.h"
#include "EchoParams.h"
#include "EchoEffect.h"
#include "FilterParams.h"
#include "HighPassEffect.h"
#include "LowPassEffect.h"
#include "VolumeEffect.h"

extern "C" {
#include "sox.h"
}
// 春哥(springtom) 2020-04-21


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_initSoxAudioNative(JNIEnv *env, jobject thiz,
                                                            jint buffer_size,
                                                            jint sample_rate, jint channels) {

    LOGE("init1");
    SoxManager &soxManager = SoxManager::getInstance();
    LOGE("init2");
    soxManager.initArgs(sample_rate, buffer_size, channels);
    LOGE("init3");
    return true;

}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addEqualizerEffectNative(JNIEnv *env, jobject thiz,
                                                                  jobjectArray params) {
    LOGE("addEQ1");
    int row = env->GetArrayLength(params);
    LOGE("addEQ2");
    jfloatArray paramsRow = static_cast<jfloatArray>(env->GetObjectArrayElement(params, 0));
    LOGE("addEQ3");
    int col = env->GetArrayLength(paramsRow);
    LOGE("addEQ4");
    jfloat paramsff[row][col];
    LOGE("addEQ5");
    for (int i = 0; i < row; i++) {
        LOGE("addEQ6");
        paramsRow = static_cast<jfloatArray>(env->GetObjectArrayElement(params, i));
        jfloat *coldata = env->GetFloatArrayElements(paramsRow, 0);
        for (int j = 0; j < col; j++) {
            LOGE("addEQ7");
            paramsff[i][j] = coldata[j];
            LOGE("%f", paramsff[i][j]);
        }
        LOGE("addEQ8");
        env->ReleaseFloatArrayElements(paramsRow, coldata, 0);
    }
    LOGE("addEQ9");
    list<EQParams *> *eqparamslist = new list<EQParams *>();
    LOGE("addEQ10");
    for (int i = 0; i < row; i++) {
        LOGE("addEQ11");
        EQParams *eqParams = new EQParams(paramsff[i][0], paramsff[i][1], paramsff[i][2]);
        LOGE("addEQ12");
        eqparamslist->push_back(eqParams);
        LOGE("addEQ13");
    }
    LOGE("addEQ14");
    EQEffect *effect = new EQEffect(eqparamslist);
    LOGE("addEQ15");
    effect->init();
    LOGE("addEQ16");
    SoxManager &soxManager = SoxManager::getInstance();
    LOGE("addEQ17");
    soxManager.addEffect(effect);
    LOGE("addEQ18");
    return true;

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addReverbEffectNative(JNIEnv *env, jobject thiz,
                                                               jint reverberance, jint damping,
                                                               jint room_scale, jint stereo_depth,
                                                               jint pre_delay, jint wet_gain) {
    ReverbParams *reverbParams = new ReverbParams(reverberance, damping, room_scale, stereo_depth,
                                                  pre_delay, wet_gain);
    ReverbEffect *effect = new ReverbEffect(reverbParams);
    effect->init();
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.addEffect(effect);
    return true;
}





extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addHighPassEffectNative(JNIEnv *env, jobject thiz,
                                                                 jint frequency) {
    FilterParams *filterParams = new FilterParams(frequency);
    HighPassEffect *effect = new HighPassEffect(filterParams);
    effect->init();
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.addEffect(effect);
    return true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addLowPassEffectNative(JNIEnv *env, jobject thiz,
                                                                jint frequency) {
    FilterParams *filterParams = new FilterParams(frequency);
    LowPassEffect *effect = new LowPassEffect(filterParams);
    effect->init();
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.addEffect(effect);
    return true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addEchoNative(JNIEnv *env, jobject thiz,
                                                       jfloat input_volume,
                                                       jfloat output_volume, jint delay,
                                                       jfloat attenuation) {
    EchoParams *echoParams = new EchoParams(input_volume, output_volume, delay, attenuation);
    EchoEffect *echoEffect = new EchoEffect(echoParams);
    LOGE("addEchoNative1")
    echoEffect->init();
    LOGE("addEchoNative2")
    SoxManager &soxManager = SoxManager::getInstance();
    LOGE("addEchoNative3")
    soxManager.setEchoEffect(echoEffect);
    LOGE("addEchoNative4")
    return true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_addVolAddNative(JNIEnv *env, jobject thiz, jint add_vol) {
    VolumeEffect * effect =  new VolumeEffect(add_vol);
    effect->init();
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.addEffect(effect);
    return true;
}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_doprocess(JNIEnv *env, jobject thiz,
                                                   jshortArray audio_simple,
                                                   jint size) {
    int len = size;
    jshort *audioSample = env->GetShortArrayElements(audio_simple, NULL);
    short *temp = static_cast<short *>(malloc(sizeof(short) * len));
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.doProcess(audioSample, len);
    if (len > 0) {
        memcpy(temp, audioSample, len * sizeof(short));
        jshortArray data = env->NewShortArray(len);
        env->SetShortArrayRegion(data, 0, len, temp);
        free(temp);
        env->ReleaseShortArrayElements(audio_simple, audioSample, 0);
        return data;
    }
    free(temp);
    env->ReleaseShortArrayElements(audio_simple, audioSample, 0);
    return NULL;
}extern "C"
JNIEXPORT void JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_destory(JNIEnv *env, jobject thiz) {
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.destory();
}extern "C"
JNIEXPORT void JNICALL
Java_com_aimei_meiktv_coreav_AudioEffect_setWetEchoReverbScale(JNIEnv *env, jobject thiz,
                                                               jfloat wet, jfloat echo) {
    SoxManager &soxManager = SoxManager::getInstance();
    soxManager.echoscale = echo;
    soxManager.wetscale = wet;
}
