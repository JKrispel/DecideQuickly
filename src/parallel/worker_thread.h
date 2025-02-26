#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class WorkerThread {
public:
    WorkerThread();
    virtual ~WorkerThread();

    virtual void addTask(std::function<void()> task);
    void stop();

protected:
    std::thread worker;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::queue<std::function<void()>> taskQueue;
    bool running;

    virtual void processTasks();
};
