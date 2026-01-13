#include "../include/TaskQueue.h"

TaskQueue::TaskQueue() : stopped(false) {}

TaskQueue::~TaskQueue() {
    shutdown();
}

void TaskQueue::push(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(std::move(task));
    }
    cv.notify_one(); // wake one waiting worker
}

bool TaskQueue::pop(std::function<void()>& task) {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [this] {
        return !tasks.empty() || stopped;
        });

    if (stopped && tasks.empty()) {
        return false;
    }

    task = std::move(tasks.front());
    tasks.pop();
    return true;
}

void TaskQueue::shutdown() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopped = true;
    }
    cv.notify_all(); // wake all workers to exit
}
