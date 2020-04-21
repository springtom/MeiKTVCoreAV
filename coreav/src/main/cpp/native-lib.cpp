#include <jni.h>
#include <string>
#include "Log.h"
extern "C" {
#include "sox.h"
}
// 春哥 2020-04-21
extern "C" JNIEXPORT jstring JNICALL
Java_com_aimei_meiktv_coreav_AudioHandle_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    LOGE("Hello from C++");
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

