#include "Scheduler.h"

void Scheduler::addTask(unsigned long interval, TaskCallback callback) {
    if (taskCount >= MAX_TASKS) return;

    tasks[taskCount++] = {
        interval,
        0,
        callback
    };
}

void Scheduler::run() {
    unsigned long now = millis();

    for (int i = 0; i < taskCount; i++) {
        if (now - tasks[i].lastRun >= tasks[i].interval) {
            tasks[i].lastRun = now;
            tasks[i].callback();
        }
    }
}
