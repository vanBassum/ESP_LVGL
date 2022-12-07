#pragma once
#include "esp_system.h"
#include "esp_base.h"
#include "lvgl.h"
#include "screen.h"

using namespace ESP_Base;

namespace ESP_LVGL
{
	class LVGL
	{
		static const uint32_t LVGL_HANDLER_TICK_MS  = 10;
		static const uint32_t LVGL_TIMER_TICK_MS	= 1;
		static Task task;
		static Timer timer;		
	public:
		static Mutex mutex;
		
		static esp_err_t Init()
		{
			lv_init();
			task.Init("LVGL", 7, 2048 * 4);
			task.Bind([](Task& t, void* args) {
				lv_timer_handler();
				vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
			});
			task.RunPinned(1);
	
			timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
			timer.Bind([](Timer& t) {
				lv_tick_inc(t.GetPeriod().GetMiliSeconds());
			});
			timer.Start();
			return ESP_OK;
		}
	};
}
