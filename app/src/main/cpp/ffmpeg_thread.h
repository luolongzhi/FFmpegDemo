
#ifndef _FFMPEG_THREAD_H
#define _FFMPEG_THREAD_H


#include "libavcodec/avcodec.h" 
#include "libavformat/avformat.h" 
#include "libswscale/swscale.h" 
#include "ffmpeg.h" 
#include <pthread.h> 
#include <string.h> 


#ifdef __cplusplus
extern "C" {
#endif

int ffmpeg_thread_run_cmd(int cmdnum,char **argv); 
void ffmpeg_thread_exit(int ret); 
void ffmpeg_thread_callback(void (*cb)(int ret));


#ifdef __cplusplus
}
#endif

#endif
