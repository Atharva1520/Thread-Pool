# Thread Pool Design in C++

A modern, production-style **Thread Pool implementation in C++** built from scratch using
standard concurrency primitives.

This project demonstrates how real-world backend systems manage concurrency efficiently.

---

## 🚀 Features

- Fixed-size worker thread pool
- Thread-safe task queue (producer–consumer model)
- Blocking workers using condition variables (no busy waiting)
- Generic task submission using templates
- Support for return values via std::future
- Exception-safe task execution
- Graceful shutdown with RAII
- Clean header/source separation (Visual Studio compatible)

---

## 🧠 Core Concepts Used

- std::thread
- std::mutex
- std::condition_variable
- std::atomic
- std::future / std::packaged_task
- RAII & safe shutdown patterns

---

## 📂 Project Structure

ThreadPool-Design/
│
├── include/
│ ├── ThreadPool.h
│ └── TaskQueue.h
│
├── src/
│ ├── ThreadPool.cpp
│ └── TaskQueue.cpp
│
├── main.cpp
└── README.md

yaml
Copy code

---

## ⚙️ Design Overview

### Producer–Consumer Model
- **Producer:** submit() API
- **Consumer:** worker threads
- **Shared Resource:** thread-safe TaskQueue

### Worker Lifecycle
1. Wait for task
2. Wake on notification
3. Execute task
4. Repeat until shutdown

---

## 🧩 Task Queue Design

- Uses `std::queue<std::function<void()>>`
- Protected by `std::mutex`
- Uses `std::condition_variable::wait()` with predicate
- Supports graceful shutdown

---

## 🔄 Thread Pool Design

- Threads created at initialization
- Tasks stored as `void()` callables
- Return values handled using `std::packaged_task`
- Destructor ensures:
  - Stop signal
  - Queue shutdown
  - Thread join

---
