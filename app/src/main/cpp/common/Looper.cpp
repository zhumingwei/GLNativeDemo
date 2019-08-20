//
// Created by zhumingwei on 2019-08-17.
//

#include "Looper.h"
#include "native_log.h"

Looper::Looper() {
    head = NULL;
    sem_init(&headdataavailable, 0, 0);
    sem_init(&headwriteprotect, 0, 1);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&worker, &attr , trampoline, this);
    running = true;
}

Looper::~Looper() {
    if (running){
        ALOGD("Lopper deleted whild still running, some message will not be processed");
        quit();
    }
}

/**
 * 入队消息
 * @param what
 * @param flush
 */
void Looper::postMessage(int what, bool flush) {
    postMessage(what,0,0,NULL,flush);
}

void Looper::postMessage(int what, void *obj, bool flush) {
    postMessage(what,0,0,obj,flush);
}

void Looper::postMessage(int what, int arg1, int arg2, bool flush) {
    postMessage(what, arg1, arg2, NULL , flush);
}

void Looper::postMessage(int what, int arg1, int arg2, void *obj, bool flush) {
    LooperMessage *msg = new LooperMessage();
    msg->what = what;
    msg->obj = obj;
    msg->arg1 = arg1;
    msg->arg2 = arg2;
    msg->next = NULL;
    msg->quit = false;
    addMessage(msg,flush);
}

/**
 * 退出 lopper循环
 */
void Looper::quit() {
    ALOGD("quit");
    LooperMessage *msg = new LooperMessage();
    msg->what = 0;
    msg->obj = NULL;
    msg->next = NULL;
    msg->quit = true;
    addMessage(msg, false);
    void *retval;
    pthread_join(worker, &retval);
    sem_destroy(&headwriteprotect);
    sem_destroy(&headdataavailable);
    running = false;
}

void Looper::handleMessage(LooperMessage *msg) {
    ALOGD("dropping msg %d %p", msg->what, msg->obj);
}

void Looper::addMessage(LooperMessage *msg, bool flush) {
    sem_wait(&headwriteprotect);
    LooperMessage *h = head;

    if (flush) {
        while(h) {
            LooperMessage *next = h->next;
            delete h;
            h = next;
        }
        h = NULL;
    }
    if (h) {
        while (h->next) {
            h = h->next;
        }
        h->next = msg;
    } else {
        head = msg;
    }
    ALOGD("post msg %d", msg->what);
    sem_post(&headwriteprotect);
    sem_post(&headdataavailable);
}

void *Looper::trampoline(void *p) {
    ((Looper*)p)->loop();
    return NULL;
}

void Looper::loop(void) {
    while (true){
        //wait for available mesage
        sem_wait(&headdataavailable);

        //get next available message
        sem_wait(&headwriteprotect);
        LooperMessage *msg = head;
        if (msg == NULL){
            ALOGD("no msg");
            sem_post(&headwriteprotect);
            continue;
        }
        head = msg->next;
        sem_post(&headwriteprotect);

        if (msg->quit){
            ALOGD("quitting");
            delete msg;
            return;
        }
        ALOGD("processing msg %d",msg->what);
        handleMessage(msg);
        delete msg;
    }
}




