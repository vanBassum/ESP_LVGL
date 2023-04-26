#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "lvgl.h"

namespace ESP_LVGL
{
	namespace LVGL
	{
		static const uint32_t LVGL_HANDLER_TICK_MS  = 5;	//The timing is not critical but it should be about 5 milliseconds to keep the system responsive.
		static const uint32_t LVGL_TIMER_TICK_MS	= 1;
		static Mutex mutex;
		static Task  task;
		static Timer timer;
				
		static bool Init()
		{
			lv_init();
			task.Init("LVGL", 2, 2048 * 4);
			task.Bind([](Task* t, void* args) {
				while (1)
				{
					mutex.Take();
					lv_timer_handler();
					mutex.Give();
					vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
				}
			});
			task.Run();
			
			timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
			timer.Bind([](Timer* t) { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
			timer.Start();

			return true;
		}
	}	
}
