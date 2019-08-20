//
// Created by zhumingwei on 2019-08-18.
//

#ifndef GLNATIVEDEMO_MYLOOPER_H
#define GLNATIVEDEMO_MYLOOPER_H

#include "Looper.h"
#include "../render/GLRender.h"

enum {
    kMsgSurfaceCreated,
    kMsgSurfaceChanged,
    kMsgSurfaceDestroyed
};

class MyLooper:public Looper{
public:
    MyLooper();

    virtual ~MyLooper();

    virtual void handleMessage(LooperMessage *msg);

private:
    GLRender *mRender;
};
#endif //GLNATIVEDEMO_MYLOOPER_H
