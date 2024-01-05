#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lvgl/lvgl.h"
#include <functional>
#include <type_traits>


namespace ESP_LVGL
{
    class LVGLService
    {
        constexpr static const char* TAG = "LVGLService";
    public:
        struct Config {
            ticktype_t timerIntervalms = 1;
            ticktype_t taskIntervalms = 20;
        };
        
    private:
        static int instances;
        bool initialized = false;
        int coreId = -1;
        Task task;
        Timer timer;	
        RecursiveMutex mutex;
        
        Config config = {};
        
    public:
        LVGLService()
        {
            assert(instances == 0); 	//This ensures only 1 instance can be initialized
            instances++;
        }
        ~LVGLService() = default;
        
        void init()
        {
            assert(!initialized);
            lv_init();
            
            task.Init("LVGL", 2, 1024 * 4);
            task.SetHandler([&](){this->Work();});
            task.RunPinned(0);
                    
            timer.Init("LVGL", config.taskIntervalms);
            timer.SetHandler([]() { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
            timer.Start();
            
            initialized = true;
        }
        
        void setConfig(const Config& newConfig)
        {
            assert(!initialized);
            config = newConfig;
        }

        void Work()
        {
            while (1)
            {
                {
                    ContextLock(mutex);
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
        
        
        void ExecuteSafely(std::function<void()> function)
        {
            ContextLock(mutex);
            if (coreId != Task::GetCurrentCoreID())
                ESP_LOGE(TAG, "Called LVGL function from wrong core. Use core %d", coreId);
            function();	
        }

    };
}

int LVGLService::instances = 0;
