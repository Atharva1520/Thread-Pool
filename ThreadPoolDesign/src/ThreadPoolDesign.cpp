#include <iostream>
#include <atomic>
#include "../include/ThreadPool.h"

int main() {
    ThreadPool pool(8);
    std::atomic<int> counter{ 0 };

    for (int i = 0; i < 100000; ++i) {
        auto future = pool.submit([] {
            throw std::runtime_error("Crash test");
            return 42;
            });

        try {
            future.get();
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // pool destructor waits for completion
    std::cout << "Submitted 100000 tasks\n";
}
