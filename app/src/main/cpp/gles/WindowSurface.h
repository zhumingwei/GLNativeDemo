//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_WINDOW_H
#define GLNATIVEDEMO_WINDOW_H

#include "EglSurfaceBase.h"

class WindowSurface : public EglSurfaceBase{
public:
    WindowSurface(EglCore *eglCore, ANativeWindow *window, bool releaseSurface);
    WindowSurface(EglCore *eglCore, ANativeWindow *window);
    //释放资源
    void release();
    //重新创建
    void recreate(EglCore *eglCore);

private:
    ANativeWindow *mSurface;
    bool mReleaseSurface;
};
#endif //GLNATIVEDEMO_WINDOW_H
