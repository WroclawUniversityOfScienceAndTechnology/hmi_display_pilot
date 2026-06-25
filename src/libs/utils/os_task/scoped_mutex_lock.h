/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#pragma once

#include "freertos/semphr.h"

namespace utils
{
class ScopedMutexLock
{
public:
    ScopedMutexLock(SemaphoreHandle_t mutex, TickType_t timeout = portMAX_DELAY) :
      mutex_(mutex), locked_(xSemaphoreTakeRecursive(mutex_, timeout) == pdTRUE)
    {
    }

    ~ScopedMutexLock()
    {
        if (locked_)
        {
            xSemaphoreGiveRecursive(mutex_);
        }
    }

    bool isLocked() const
    {
        return locked_;
    }

private:
    SemaphoreHandle_t mutex_;
    bool locked_;
};
}  // namespace utils
