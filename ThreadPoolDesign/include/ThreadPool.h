#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <future>
#include <type_traits>

#include "TaskQueue.h"

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void workerLoop();

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>;

private:
    std::vector<std::thread> workers;
    TaskQueue taskQueue;
    std::atomic<bool> stop{ false };
};

template<typename F, typename... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
-> std::future<std::invoke_result_t<F, Args...>>
{
    using ReturnType = std::invoke_result_t<F, Args...>;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<ReturnType> result = task->get_future();

    if (!stop.load()) {
        taskQueue.push([task]() { (*task)(); });
    }

    return result;
}
