#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include <queue>

#if 1
template <class T>
class BlockingQueue
{
public:
    BlockingQueue(int capacity)
        :capacity_(capacity)
    {
        pthread_mutex_init(&mutex_, nullptr);
        pthread_cond_init(&full_, nullptr);
        pthread_cond_init(&empty_, nullptr);
    }

    ~BlockingQueue()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&full_);
        pthread_cond_destroy(&empty_);
    }

    void Push(const T data)
    {
        LockQueue();

        while (IsFull())
        {
            NotifyConsume();

            std::cout << "The Queue is full, please wait..." << std::endl;

            ProducerWait();
        }

        qu_.push(data);

        NotifyConsume();

        UnlockQueue();
    }


    void Pop(T* data) // data 作为输出型参数
    {
        LockQueue();

        while (IsEmpty())
        {
            NotifyProducer();

            std::cout << "Queue is empty, please wait..." << std::endl;

            ConsumeWait();
        }

        *data = qu_.front();
        qu_.pop();

        NotifyProducer();

        UnlockQueue();
    }

private:

    void LockQueue()
    {
        pthread_mutex_lock(&mutex_);
    }

    void NotifyConsume()
    {
        pthread_cond_signal(&full_);
    }

    void NotifyProducer()
    {
        pthread_cond_signal(&empty_);
    }

    void ProducerWait()
    {
        pthread_cond_wait(&empty_, &mutex_);
    }

    void ConsumeWait()
    {
        pthread_cond_wait(&full_, &mutex_);
    }

    void UnlockQueue()
    {
        pthread_mutex_unlock(&mutex_);
    }

    bool IsFull()
    {
        return qu_.size() == capacity_ ? true : false;
    }

    bool IsEmpty()
    {
        return qu_.empty();
    }
private:
    pthread_mutex_t mutex_;
    pthread_cond_t full_;
    pthread_cond_t empty_;
    std::queue<T> qu_;
    size_t capacity_;
};
#endif 

