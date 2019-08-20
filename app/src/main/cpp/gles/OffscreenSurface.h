//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_OFFSCREENSURFACE_H
#define GLNATIVEDEMO_OFFSCREENSURFACE_H

#include "EglSurfaceBase.h"

class OffscreenSurface : public EglSurfaceBase {
public:
    OffscreenSurface(EglCore *eglCore, int width, int height);

    void release();
};

#endif //GLNATIVEDEMO_OFFSCREENSURFACE_H
