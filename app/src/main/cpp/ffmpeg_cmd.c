#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "ffmpeg_cmd.h"
#include "ffmpeg_thread.h"

static JavaVM *g_jvm = NULL;
static jclass g_clazz = NULL;

static void ffmpeg_onfinished_callback(int ret) {
    JNIEnv *env;

    (*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL);

    if (g_clazz == NULL) {
        return;
    }

    jmethodID methodID = (*env)->GetStaticMethodID(env, g_clazz, "onFinished", "(I)V");
    if (methodID == NULL) {
        return;
    }

    (*env)->CallStaticVoidMethod(env, g_clazz, methodID, ret);

    (*g_jvm)->DetachCurrentThread(g_jvm);

}


static void ffmpeg_onerror_callback(int errCode) {
    JNIEnv *env;

    (*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL);

    if (g_clazz == NULL) {
        return;
    }

    jmethodID methodID = (*env)->GetStaticMethodID(env, g_clazz, "onError", "(I)V");
    if (methodID == NULL) {
        return;
    }

    (*env)->CallStaticVoidMethod(env, g_clazz, methodID, errCode);

    (*g_jvm)->DetachCurrentThread(g_jvm);
}




static void set_all_callback() {
    ffmpeg_set_onfinished_callback(ffmpeg_onfinished_callback);
    ffmpeg_set_onerror_callback(ffmpeg_onerror_callback);
}


jint Java_com_xaudiopro_ffmpeg_FFmpegCmd_exec(JNIEnv *env, jclass clazz, jint cmdnum, jobjectArray cmdline) {

    //保存java虚拟机环境变量及class 全局引用
    (*env)->GetJavaVM(env, &g_jvm);
    g_clazz = (*env)->NewGlobalRef(env, clazz);

    int i = 0;
    char **argv = NULL;
    jstring *strr = NULL;

    if (cmdline != NULL) {
        argv = (char **) malloc(sizeof(char *) * cmdnum);
        strr = (jstring *) malloc(sizeof(jstring) * cmdnum);

        for (i = 0; i < cmdnum; i++) {
             strr[i] = (jstring)(*env)->GetObjectArrayElement(env, cmdline, i); 
             argv[i] = (char *) (*env)->GetStringUTFChars(env, strr[i], 0);
        }
    }
    
    //set all callback
    set_all_callback();

    ffmpeg_thread_run_cmd(cmdnum, argv);

    if (cmdline != NULL) {
        for (i = 0; i < cmdnum; i++) {
            (*env)->DeleteLocalRef(env, strr[i]);

            //TODO pass argv and release it later
            /*(*env)->ReleaseStringUTFChars(env, cmdline, argv[i]);*/
        }
    }

    free(strr);

    return 0;
}


