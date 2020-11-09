#include "MsgQueue.h"


MsgQueue::MsgQueue(unsigned long maxSize)
{
    maxSize_ = maxSize > 0 ? maxSize : 1;
}

void MsgQueue::send(unsigned long id, Message* msg)
{
    
    pthread_mutex_lock(&mtx);

    while(container_.size() >= maxSize_)
    {
        pthread_cond_wait(&cond, &mtx);
    }
    Msg sendMsg;
    sendMsg.id_ = id;
    sendMsg.msg_ = msg;
    container_.push(sendMsg);

    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long &id)
{
    pthread_mutex_lock(&mtx);

    while(container_.empty())
    {
        pthread_cond_wait(&cond, &mtx);
    }

    Msg receiveMsg = container_.front();
    id = container_.front().id_;

    container_.pop();

    

    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
    
    return receiveMsg.msg_;
}


MsgQueue::~MsgQueue()
{
    delete &container_;
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mtx);
}