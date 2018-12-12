package com.xaudiopro.ffmpeg;

import android.app.ProgressDialog;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    public ProgressDialog show;


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("avutil");
        System.loadLibrary("swresample");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("avfilter");
        System.loadLibrary("avdevice");
        System.loadLibrary("native-lib");
    }

    //private FFmpegCmd mFFmpegCmd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final String path = Environment.getExternalStorageDirectory().getPath();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
        //String a = mFFmpegCmd.testCmd();

        findViewById(R.id.btnCutAudio).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //String cmd = "ffmpeg -y -i " + path + "/1.mp4" + " -f adts " + path + "/1out.aac";
                String cmd = "ffmpeg -y -i " + path + "/pm.mp3" + " -f wav " + path + "/pm.wav";
                toExec(cmd);
            }

        });



        tv.setText("uuuuuuuu");
    }

    private void toExec(String cmd) {
        show = ProgressDialog.show(MainActivity.this, null, "执行中...", true);
        //转换为数组
        String[] cmds = cmd.split(" ");

        FFmpegCmd.exec(cmds, new FFmpegCmd.OnExecListener() {
            @Override
            public void onExecuted(final int ret) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Log.v("uuuuuuuuuuiiii", "jjjj");
                        Toast.makeText(MainActivity.this, "执行完成=" + ret, Toast.LENGTH_SHORT).show();
                        show.dismiss();
                    }
                });
            }


        });


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
