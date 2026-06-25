/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */

#pragma once

#include "os_task.h"
#include <vector>
#include <memory>

namespace utils
{
class OsTaskManager
{
public:
    // Constructor and destructor
    OsTaskManager();
    ~OsTaskManager() = default;

    // Add a task to the manager
    void addTask(std::unique_ptr<OsTask> task);

    // Start all tasks managed by the manager
    void startAll();

    // Stop all tasks managed by the manager
    void stopAll();

    // Get the number of tasks
    size_t getTaskCount() const;

private:
    // Container for the tasks
    std::vector<std::unique_ptr<OsTask>> tasks_;
};
}  // namespace utils
