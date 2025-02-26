#include "parallel/ai_worker_thread.h"
#include <iostream>

AIWorkerThread::AIWorkerThread() : WorkerThread() {}

AIWorkerThread::~AIWorkerThread() {}

void AIWorkerThread::addTask(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(queueMutex);

    while (!taskQueue.empty()) {
        taskQueue.pop();
    }

    taskQueue.push(task);
    condition.notify_one();
}
