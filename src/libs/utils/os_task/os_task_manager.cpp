/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#include "os_task_manager.h"

using namespace utils;  // NOLINT(readability-identifier-naming)

OsTaskManager::OsTaskManager()
{
    OsTask::initializeTaskWatchdog();
}

// // Add a task to the manager
void OsTaskManager::addTask(std::unique_ptr<OsTask> task)
{
    tasks_.emplace_back(std::move(task));
}

// Start all tasks managed by the manager
void OsTaskManager::startAll()
{
    for (auto& task : tasks_)
    {
        if (!task->isRunning())
        {
            task->init();
            task->run();
        }
    }
}

// Stop all tasks managed by the manager
void OsTaskManager::stopAll()
{
    for (auto& task : tasks_)
    {
        task->destroy();
    }
}

// Get the number of tasks managed
size_t OsTaskManager::getTaskCount() const
{
    return tasks_.size();
}
