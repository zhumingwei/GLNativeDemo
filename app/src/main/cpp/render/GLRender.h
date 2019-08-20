//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_GLRENDER_H
#define GLNATIVEDEMO_GLRENDER_H
#include <android/native_window.h>
#include "../gles/EglSurfaceBase.h"
#include "../gles/WindowSurface.h"
#include "Triangle.h"

class GLRender{
public:
    GLRender();

    virtual ~GLRender();

    void surfaceCreated(ANativeWindow *window);

    void surfaceChanged(int width, int height);
    void surfaceDestroyed(void);

private:
    EglCore *mEglCore;
    WindowSurface *mWindowSurface;
    Triangle *mTriangle;
};
#endif //GLNATIVEDEMO_GLRENDER_H
