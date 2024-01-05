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
            uint32_t timerIntervalms = 1;
            uint32_t taskIntervalms = 20;
        };
        
    private:
        static int instances;
        bool initialized = false;
        int coreId = -1;
        Task task;
        Timer timer;	
        RecursiveMutex mutex;
        
        Config config = {};

        void Work();
        
    public:
        LVGLService();
        ~LVGLService() = default;
        
        void init();
        void setConfig(const Config& newConfig);
        void executeSafely(std::function<void()> function);

    };

}

