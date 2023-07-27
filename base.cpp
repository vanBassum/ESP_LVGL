#include "base.h"
#include "esp_log.h"

static const char* TAG = "LVGL";
	
ESP_LVGL::LVGL ESP_LVGL::LVGL::_Instance;



void ESP_LVGL::LVGL::_Start()
{
	task.Init("LVGL", 2, 2048 * 4);
	task.Bind(this, &ESP_LVGL::LVGL::_Work);
	task.RunPinned(1);
			
	timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
	timer.Bind([](Timer* t) { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
	timer.Start();
}

void ESP_LVGL::LVGL::_Work(Task* t, void* args)
{
	mutex.Take();
	coreId = Task::GetCurrentCoreID();
	mutex.Give();
	while (1)
	{
		mutex.Take();
		lv_timer_handler();
		mutex.Give();
		vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
	}
}


void ESP_LVGL::LVGL::_Execute(std::function<void()> val)
{
	bool started = false;
	mutex.Take();
	started = coreId != -1;
	mutex.Give();
	
	if(started == false)
	{
		ESP_LOGE(TAG, "LVGL task not started");
		return;
	}
	
	if (coreProtection)
	{
		int currentCore = Task::GetCurrentCoreID();
		if (coreId != currentCore)
		{
			ESP_LOGE(TAG, "Called LVGL function from wrong core. Use core %d", coreId);
			return;
		}
	}
	
	mutex.Take();
	val();
	mutex.Give();
}
	



