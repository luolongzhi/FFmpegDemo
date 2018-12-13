#include "ffmpeg_thread.h" 

pthread_t ntid; 
char **argvs = NULL; 
int num=0; 
static void (*ffmpeg_onfinished_callback)(int ret); 

void *thread(void *arg) { 
    int result = ffmpeg_exec(num, argvs); 
    return ((void *)0); 
} 

/**
 * 新建子线程执行ffmpeg命令
 */ 
int ffmpeg_thread_run_cmd(int cmdnum, char **argv) { 
    num = cmdnum; 
    argvs = argv; 

    int temp = pthread_create(&ntid, NULL, thread, NULL); 
    if (temp!=0) { 
        //LOGE("can't create thread: %s ",strerror(temp)); 
        return 1; 
    } 
    
    return 0; 
} 


void ffmpeg_set_onfinished_callback(void (*cb)(int ret)) { 
    ffmpeg_onfinished_callback = cb; 
} 

void ffmpeg_thread_exit(int ret) { 
    if (ffmpeg_onfinished_callback) { 
        ffmpeg_onfinished_callback(ret); 
    } 
    
    pthread_exit("ffmpeg_thread_exit"); 
}
