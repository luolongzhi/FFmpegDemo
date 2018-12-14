package com.xaudiopro.ffmpeg;

public class FFmpegCmd {

    //全局单例回调监听
    private static OnExecListener listener;

    //ffmpeg 命令执行函数(C native 接口函数)
    public native static int exec(int argc, String[] argv);

    //命令执行完成函数, C端反射回调使用
    public static void onPrepared(int duration) {
        //判断上层java层监听是否设置，设置后执行回调
        if (listener != null) {
            listener.onPrepared(duration);
        }
    }

    public static void onFinished(int ret) {
        //判断上层java层监听是否设置，设置后执行回调
        if (listener != null) {
            listener.onFinished(ret);
        }
    }

    public static void onError(int errCode) {
        if (listener != null) {
            listener.onError(errCode);
        }
    }

    public static void onStep(int size, int hour, int min, int sec, int us) {
        if (listener != null) {
            listener.onStep(size, hour, min, sec, us);
        }
    }

    //Java层调用exec执行命令函数
    public static void exec(String[] cmds, OnExecListener listener) {
        FFmpegCmd.listener = listener;
        exec(cmds.length, cmds);
    }

    public interface OnExecListener {
        void onPrepared(int duration);
        void onFinished(int ret);
        void onError(int errCode);
        void onStep(int size, int hour, int min, int sec, int us);
    }


}
