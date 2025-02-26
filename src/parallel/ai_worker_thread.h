#pragma once
#include "parallel/worker_thread.h"

class AIWorkerThread : public WorkerThread {
public:
    AIWorkerThread();
    ~AIWorkerThread();

    void addTask(std::function<void()> task) override;
};
