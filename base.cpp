#include "base.h"
#include "esp_log.h"

static const char* TAG = "LVGL";

ESP_LVGL::LVGL ESP_LVGL::LVGL::_Instance;

bool ESP_LVGL::LVGL::_Init()
{
	lv_init();
	task.Init("LVGL", 2, 2048 * 4);
	task.Bind([](Task* t, void* args) {
		_Instance.coreId = Task::GetCurrentCoreID();
		while (1)
		{
			_Instance.mutex.Take();
			lv_timer_handler();
			_Instance.mutex.Give();
			vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
		}
	});
	task.RunPinned(1);
			
	timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
	timer.Bind([](Timer* t) { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
	timer.Start();

	return true;
}



void ESP_LVGL::LVGL::_Execute(std::function<void()> val)
{
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
	
