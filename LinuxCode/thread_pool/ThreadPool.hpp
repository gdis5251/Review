#pragma once
#include "BlockingQueue.hpp"

#if 0
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
#endif 

class Task
{
public:
    virtual void Run() = 0; // 定义一个纯虚函数，需要用户在定义任务的时候进行重写

    virtual ~Task(){}       // 将析构函数定义为虚函数，防止内存泄漏
};

class ThreadPool
{
public:
    ThreadPool(int n)
        :workers_(n)
        ,task_(100)
        ,worker_num_(n)
    {
        // 创建 n 个线程阻塞等待任务
        for (int i = 0; i < n; i++)
        {
            pthread_t tid;
            pthread_create(&tid, nullptr, ThreadEntry, this);
            workers_.push_back(tid);
        }
    }

    ~ThreadPool()
    {
        // 先将 n 个线程结束
        for (size_t i = 0; i < worker_num_; i++)
        {
            pthread_cancel(workers_[i]);
        }
        // 再逐个等待每个线程
        for (size_t i = 0; i < worker_num_; i++)
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
        }

        return nullptr;
    }
private:
    // 有一个队列来存放线程 tid
    std::vector<pthread_t> workers_;
    // 需要一个阻塞队列来存放任务
    BlockingQueue<Task*> task_;

    size_t worker_num_;
};
