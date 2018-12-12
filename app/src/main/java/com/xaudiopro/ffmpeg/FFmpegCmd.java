package com.xaudiopro.ffmpeg;

public class FFmpegCmd {

    //static {
        //System.loadLibrary("avutil");
        //System.loadLibrary("swresample");
        //System.loadLibrary("avcodec");
        //System.loadLibrary("avformat");
        //System.loadLibrary("swscale");
        //System.loadLibrary("avfilter");
        //System.loadLibrary("avdevice");
    //}

    private static OnExecListener listener;

    public native static int exec(int argc, String[] argv);
    public static void onExecuted(int ret) {
        if (listener != null) {
            listener.onExecuted(ret);
        }
    }

    public static void exec(String[] cmds, OnExecListener listener) {
        FFmpegCmd.listener = listener;
        exec(cmds.length, cmds);
    }

    public interface OnExecListener {
        void onExecuted(int ret);
    }


    public native String testCmd();




}
