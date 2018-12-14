
#ifndef _FFMPEG_THREAD_H
#define _FFMPEG_THREAD_H


#include "libavcodec/avcodec.h" 
#include "libavformat/avformat.h" 
#include "libswscale/swscale.h" 
#include "ffmpeg.h" 
#include <pthread.h> 
#include <string.h> 
#include <jni.h>


#ifdef __cplusplus
extern "C" {
#endif

int ffmpeg_thread_run_cmd(int cmdnum,char **argv); 


//回调函数通知java调用
void ffmpeg_set_duration(int duration);
void ffmpeg_set_onprepared_callback(void (*cb)(int duration));
void ffmpeg_onprepared();

void ffmpeg_set_onfinished_callback(void (*cb)(int ret));
void ffmpeg_thread_exit(int ret); 

void ffmpeg_set_onerror_callback(void (*cb)(int err_code));
void ffmpeg_onerror(int err_code);

void ffmpeg_set_onstep_callback(void (*cb)(int size, int hour, int min, int sec, int us));
void ffmpeg_onstep(int size, int hour, int min, int sec, int us);


#ifdef __cplusplus
}
#endif

#endif
