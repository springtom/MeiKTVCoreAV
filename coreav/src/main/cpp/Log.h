
#ifndef FFPLAYER_LOG_H
#define FFPLAYER_LOG_H
#include <android/log.h>

#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"春哥native",FORMAT,##__VA_ARGS__);
#endif //FFPLAYER_LOG_H
