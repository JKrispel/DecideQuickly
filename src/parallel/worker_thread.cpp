#include "parallel/worker_thread.h"

WorkerThread::WorkerThread() : running(true) {
    worker = std::thread(&WorkerThread::processTasks, this);
}

WorkerThread::~WorkerThread() {
    stop();
    if (worker.joinable()) worker.join();
}

void WorkerThread::addTask(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.push(task);
    condition.notify_one();
}

void WorkerThread::stop() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        running = false;
    }
    condition.notify_one();
}

void WorkerThread::processTasks() {
    while (running) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !taskQueue.empty() || !running; });

            if (!running) return;
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task();
    }
}
