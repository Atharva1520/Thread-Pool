#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class TaskQueue {
public:
    TaskQueue();
    ~TaskQueue();

    void push(std::function<void()> task);

    // Blocks until task available OR shutdown
    bool pop(std::function<void()>& task);

    void shutdown();

private:
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stopped;
};

#endif
