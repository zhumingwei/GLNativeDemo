package com.zhumingwei.glnativedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements SurfaceHolder.Callback {

    static {
        System.loadLibrary("nativeEgl");
    }

    private native void nativeInit();
    private native void nativeRelease();
    private native void onSurfaceCreated(Surface surface);
    private native void onSurfaceChanged(int width, int height);
    private native void onSurfaceDestroyed();

    private SurfaceView mSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        nativeInit();
        mSurfaceView = (SurfaceView) findViewById(R.id.surface_view);
        mSurfaceView.getHolder().addCallback(this);
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        onSurfaceCreated(surfaceHolder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        onSurfaceChanged(width,height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        onSurfaceDestroyed();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeRelease();
    }
}
