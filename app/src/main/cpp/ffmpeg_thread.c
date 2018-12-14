#include "ffmpeg_thread.h" 

pthread_t ntid; 
char **argvs = NULL; 
int num=0; 

static void (*ffmpeg_onfinished_callback)(int ret); 
static void (*ffmpeg_onerror_callback)(int err_code);
static void (*ffmpeg_onstep_callback)(int size, int hour, int min, int sec, int us);

void *thread(void *arg) { 
    int result = ffmpeg_exec(num, argvs); 
    return ((void *)0); 
} 

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


//执行完成回调或退出回调及外部调用函数
void ffmpeg_set_onfinished_callback(void (*cb)(int ret)) { 
    ffmpeg_onfinished_callback = cb; 
} 

void ffmpeg_thread_exit(int ret) { 
    if (ffmpeg_onfinished_callback) { 
        ffmpeg_onfinished_callback(ret); 
    } 
    
    pthread_exit("ffmpeg_thread_exit"); 
}


//错误回调
void ffmpeg_set_onerror_callback(void (*cb)(int err_code)) {
    ffmpeg_onerror_callback = cb;
}

void ffmpeg_onerror(int err_code) {
    if (ffmpeg_onerror_callback){
        ffmpeg_onerror_callback(err_code);
    }

   // pthread_exit("ffmpeg_thread_exit");
}

//step回调
void ffmpeg_set_onstep_callback(void (*cb)(int size, int hour, int min, int sec, int us)) {
    ffmpeg_onstep_callback = cb;
}

void ffmpeg_onstep(int size, int hour, int min, int sec, int us) {
    if (ffmpeg_onstep_callback){
        ffmpeg_onstep_callback(size, hour, min, sec, us);
    }
}


