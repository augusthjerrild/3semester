#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
#include "Message.h"



using namespace std;



class MsgQueue
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg_ = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();

private:

    struct Msg
    {
        unsigned long id_;
        Message* msg_;
    };
    unsigned long maxSize_;
    queue<Msg> container_;
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

};