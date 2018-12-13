#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "ffmpeg_cmd.h"
#include "ffmpeg_thread.h"


static JavaVM *jvm = NULL;
//java虚拟机
static jclass m_clazz = NULL;//当前类(面向java)

//回调执行Java方法，参考Jni反射+Java反射
void callJavaMethod(JNIEnv *env, jclass clazz, int ret) {
    if (clazz == NULL) {
        //LOGE("---------------------------class isNULL-------------------------------");
        return;
    }

    //获取方法ID 通过javap -s -public FFmpegCmd命令生成
    jmethodID methodID = (*env)->GetStaticMethodID(env, clazz, "onExecuted", "(I)V");
    if (methodID == NULL) {
        //LOGE("--------------------------methodID is NULL----------------------------");
        return;
    }

    (*env)->CallStaticVoidMethod(env, clazz, methodID, ret);
}

static void ffmpeg_callback(int ret) {
    JNIEnv *env;

    (*jvm)->AttachCurrentThread(jvm, &env, NULL);
    callJavaMethod(env, m_clazz, ret);

    (*jvm)->DetachCurrentThread(jvm);
}


jint Java_com_xaudiopro_ffmpeg_FFmpegCmd_exec(JNIEnv *env, jclass clazz, jint cmdnum, jobjectArray cmdline) {

    //保存java虚拟机环境变量及class 全局引用
    (*env)->GetJavaVM(env, &jvm);
    m_clazz = (*env)->NewGlobalRef(env, clazz);

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
    
    ffmpeg_thread_run_cmd(cmdnum, argv);
    ffmpeg_thread_callback(ffmpeg_callback);

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


