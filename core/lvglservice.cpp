#include "lvglservice.h"


    
int ESP_LVGL::LVGLService::instances = 0;

void ESP_LVGL::LVGLService::Work()
{
    while (1)
    {
        {
            ContextLock lock(mutex);
            if (coreId == -1)
            {
                coreId = Task::GetCurrentCoreID();
                ESP_LOGI(TAG, "Running on core %d", coreId);
            }
            
            lv_timer_handler();
        }
        vTaskDelay(pdMS_TO_TICKS(config.taskIntervalms));
    }
}

ESP_LVGL::LVGLService::LVGLService()
{
    assert(instances == 0); 	//This ensures only 1 instance can be initialized
    instances++;
}

void ESP_LVGL::LVGLService::init()
{
    assert(!initialized);
    lv_init();
    
    task.Init("LVGL", 2, 1024 * 4);
    task.SetHandler([&](){this->Work();});
    task.RunPinned(0);
            
    timer.Init("LVGL", config.taskIntervalms);
    timer.SetHandler([&](){ lv_tick_inc(config.taskIntervalms); });
    timer.Start();
    
    initialized = true;
}

void ESP_LVGL::LVGLService::setConfig(const Config &newConfig)
{
    assert(!initialized);
    config = newConfig;
}

void ESP_LVGL::LVGLService::executeSafely(std::function<void()> function)
{
    ContextLock lock(mutex);
    if (coreId != Task::GetCurrentCoreID())
        ESP_LOGE(TAG, "Called LVGL function from wrong core. Use core %d", coreId);
    function();	
}

