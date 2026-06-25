#include <os_task.h>
#include <os_task_manager.h>
#include <led_task.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>

#include <memory>
#include <esp_log.h>

constexpr char const* const TAG = "MAIN";

extern "C"
{
    void app_main(void);  // NOLINT(readability-identifier-naming): name required by freertos
}


void initNvsFlash()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

/**
 * @brief Main freeRTOS task
 *
 */
void app_main(void)  // NOLINT(readability-identifier-naming): name required by freertos
{
    initNvsFlash();

    utils::OsTaskManager task_manager;

    auto led_task = std::make_unique<tasks::LedTask>();
    task_manager.addTask(std::move(led_task));

    ESP_LOGI(TAG, "Added %d tasks to the manager", task_manager.getTaskCount());
    ESP_LOGI(TAG, "Starting all tasks...");
    task_manager.startAll();

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
