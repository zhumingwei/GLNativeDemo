#include <assert.h>
#include "WindowSurface.h"

WindowSurface::WindowSurface(EglCore *eglCore, ANativeWindow *window, bool releaseSurface)
        : EglSurfaceBase(eglCore) {
    mSurface = window;
    createWindowSurface(mSurface);
    mReleaseSurface = releaseSurface;
}

WindowSurface::WindowSurface(EglCore *eglCore, ANativeWindow *window)
        : EglSurfaceBase(eglCore) {
    createWindowSurface(window);
    mSurface = window;
}

void WindowSurface::release() {
    releaseEglSurface();
    if (mSurface != NULL) {
        ANativeWindow_release(mSurface);
        mSurface = NULL;
    }

}

void WindowSurface::recreate(EglCore *eglCore) {
    assert(mSurface != NULL);
    if (mSurface == NULL) {
        ALOGE("not yet implemented ANativeWindow");
        return;
    }
    mEglCore = eglCore;
    createWindowSurface(mSurface);
}