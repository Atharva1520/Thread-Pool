#include "../include/ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount)
    : stop(false) {

    for (size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back(&ThreadPool::workerLoop, this);
    }
}

ThreadPool::~ThreadPool() {
    stop.store(true);
    taskQueue.shutdown();

    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void ThreadPool::workerLoop() {
    while (!stop.load()) {
        std::function<void()> task;

        if (!taskQueue.pop(task)) {
            break;
        }

        task();
    }
}
