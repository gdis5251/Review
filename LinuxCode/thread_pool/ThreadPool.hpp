#pragma once
#include "BlockingQueue.hpp"

class Task
{
public:
    virtual void Run() = 0;

    virtual ~Task()
    {}
};

class ThreadPool
{
public:
    ThreadPool(int n)
        :task_(100)
        ,worker_(n)
    {
        // 创建 n 个线程
        for (size_t i = 0; i < worker_; i++)
        {
            pthread_t tid;
            pthread_create(&tid, nullptr, ThreadEntry, this);
            workers_.push_back(tid);
        }
    }


    ~ThreadPool()
    {
        // 先结束线程
        for (size_t i = 0; i < worker_; i++)
        {
            pthread_cancel(workers_[i]);
        }

        for (size_t i = 0; i < worker_; i++)
        {
            pthread_join(workers_[i], nullptr);
        }
    }

    void AddTask(Task* task)
    {
        task_.Push(task);
    }

private:
    static void* ThreadEntry(void* arg)
    {
        ThreadPool* pool = (ThreadPool*)arg;
        while (true)
        {
            Task* task = nullptr;

            pool->task_.Pop(&task);
            task->Run();
            delete task;
        }
        return nullptr;
    }

private:
    BlockingQueue<Task*> task_;
    size_t worker_;
    std::vector<pthread_t> workers_;
};
