#include <jni.h>
#include <string>
#include "common/MyLooper.h"
#include "common/Looper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

MyLooper *mLooper = NULL;
ANativeWindow *mWindow = NULL;


extern "C" JNIEXPORT jstring JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_nativeInit(JNIEnv *env, jobject instance) {

    mLooper = new MyLooper();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_nativeRelease(JNIEnv *env, jobject instance) {

    if (mLooper != NULL) {
        mLooper->quit();
        delete mLooper;
        mLooper = NULL;
    }
    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = NULL;
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_onSurfaceCreated(JNIEnv *env, jobject instance,
                                                               jobject surface) {

    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = NULL;
    }
    mWindow = ANativeWindow_fromSurface(env, surface);
    if (mLooper) {
        mLooper->postMessage(kMsgSurfaceCreated, mWindow);
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                               jint width, jint height) {

    if (mLooper) {
        mLooper->postMessage(kMsgSurfaceChanged, width, height);
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_zhumingwei_glnativedemo_MainActivity_onSurfaceDestroyed(JNIEnv *env, jobject instance) {

    if (mLooper) {
        mLooper->postMessage(kMsgSurfaceDestroyed);
    }

}