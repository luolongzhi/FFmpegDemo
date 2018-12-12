#ifndef _FFMPEG_CMD_H
#define _FFMPEG_CMD_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL
Java_com_xaudiopro_ffmpeg_FFmpegCmd_exec(JNIEnv *env, jclass clazz, jint cmdnum, jobjectArray cmdline);

#ifdef __cplusplus
}
#endif
#endif
