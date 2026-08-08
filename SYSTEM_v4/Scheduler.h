#pragma once
#include <Arduino.h>

#include "config.h"

typedef void (*TaskCallback)();

struct Task {
    unsigned long interval;
    unsigned long lastRun;
    TaskCallback callback;
};

class Scheduler {
public:
    void addTask(unsigned long interval, TaskCallback callback);
    void run();

private:
    static const int MAX_TASKS = 10;
    Task tasks[MAX_TASKS];
    int taskCount = 0;
};
