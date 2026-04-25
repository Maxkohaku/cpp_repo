#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    // 提交任务
    template<typename F>
    void enqueue(F&& f);

private:
    // 工作线程函数
    void worker();

    std::vector<std::thread> workers;                       // 工作线程
    std::queue<std::function<void()>> tasks;                // 任务队列
    std::mutex queueMutex;                                  // 互斥锁保护任务队列
    std::condition_variable condition;                       // 条件变量
    std::atomic<bool> stop;                                 // 停止标志
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { worker(); });
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();  // 唤醒所有线程
    for (std::thread &worker : workers) {
        worker.join();        // 等待线程结束
    }
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // 等待条件变量，直到有任务或停止标志被设置
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) return; // 如果停止且没有任务，退出
            task = std::move(tasks.front());   // 取出任务
            tasks.pop();
        }
        task();  // 执行任务
    }
}

template<typename F>
void ThreadPool::enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(std::forward<F>(f));  // 添加任务到队列
    }
    condition.notify_one(); // 通知一个工作线程
}
#endif /*_THREAD_POOL_H_*/