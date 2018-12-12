#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "test.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_xaudiopro_ffmpeg_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_xaudiopro_ffmpeg_FFmpegCmd_testCmd(JNIEnv *env, jobject instance) {

    // TODO

    //return env->NewStringUTF(returnValue);
    return env->NewStringUTF("haha");
}



