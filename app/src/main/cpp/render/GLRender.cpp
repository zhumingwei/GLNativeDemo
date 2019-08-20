//
// Created by zhumingwei on 2019-08-17.
//

#include "GLRender.h"
//#include "../gles/GLUtils.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <cassert>

void GLRender::surfaceDestroyed(void) {
    if (mTriangle){
        mTriangle->destroy();
        delete mTriangle;
        mTriangle = NULL;
    }
    if (mWindowSurface) {
        mWindowSurface->release();
        delete mTriangle;
        mTriangle = NULL;
    }
    if (mEglCore){
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }

}

void GLRender::surfaceChanged(int width, int height) {
    mWindowSurface -> makeCurrent();
    mTriangle -> onDraw(width, height);
    mWindowSurface->swapBuffers();
}

void GLRender::surfaceCreated(ANativeWindow *window) {

    if (mEglCore == NULL){
        mEglCore = new EglCore(NULL, FLAG_RECORDABLE);
    }
    mWindowSurface = new WindowSurface(mEglCore, window,false);
    assert(mWindowSurface != NULL && mEglCore != NULL);
    mWindowSurface -> makeCurrent();
    mTriangle = new Triangle();
    mTriangle-> init();
}

GLRender::GLRender() {
    mEglCore = NULL;
    mWindowSurface = NULL;
}

GLRender::~GLRender() {
    if (mEglCore){
        mEglCore->release();
        delete  mEglCore;
        mEglCore = NULL;
    }
}
