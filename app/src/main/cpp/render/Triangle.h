//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_TRIANGLE_H
#define GLNATIVEDEMO_TRIANGLE_H

#include "../gles/GLUtils.h"
#include "../gles/GLShaders.h"
#include "../common/native_log.h"

class Triangle{
public:
    Triangle();

    virtual  ~Triangle();

    int init(void);

    void onDraw(int width, int height);

    void destroy();

private:
    int programHandle;

};

#endif //GLNATIVEDEMO_TRIANGLE_H
