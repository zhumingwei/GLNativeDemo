//
// Created by zhumingwei on 2019-08-17.
//

#ifndef GLNATIVEDEMO_LOOPER_H
#define GLNATIVEDEMO_LOOPER_H

#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

struct LooperMessage {
    int what;
    int arg1;
    int arg2;
    void *obj;
    LooperMessage *next;
    bool quit;
};

class Looper {
public:
    Looper();
    //删除默认拷贝构造函数，即不能进行默认拷贝
    Looper&operator=(const Looper&) = delete;
    //删除默认构造函数
    Looper(Looper&)= delete;
    virtual ~Looper();

    //发送消息
    void postMessage(int what, bool flush =false);
    void postMessage(int what, void *obj, bool flush = false);
    void postMessage(int what, int arg1, int arg2, bool flush =false);
    void postMessage(int what, int arg1, int arg2, void *obj, bool flush = false);
    //退出Lopper循环
    void quit();
    //处理消息
    virtual void handleMessage(LooperMessage *msg);

private:
    //添加消息
    void addMessage(LooperMessage *msg, bool flush);

    //消息线程句柄
    static  void *trampoline(void *p);

    //循环体
    void loop(void);

    LooperMessage *head;
    pthread_t worker;
    sem_t headwriteprotect;
    sem_t headdataavailable;
    bool running;
};
#endif //GLNATIVEDEMO_LOOPER_H
