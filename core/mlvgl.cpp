#include "mlvgl.h"

Mutex ESP_LVGL::LVGL::singletonMutex;
ESP_LVGL::LVGL* ESP_LVGL::LVGL::instance {NULL};

ESP_LVGL::LVGL::LVGL()
{
	lv_init();
	
	task.Init("LVGL", 2, 2048 * 4);
	task.Bind(this, &ESP_LVGL::LVGL::Work);
	task.RunPinned(1);
			
	timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
	timer.Bind([](Timer* t) { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
	timer.Start();
}


void ESP_LVGL::LVGL::Work(Task* task, void* args)
{
	mutex.Take();
	coreId = Task::GetCurrentCoreID();	//Note the coreId.
	mutex.Give();
	
	while (1)
	{
		mutex.Take();
		lv_timer_handler();
		mutex.Give();
		vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
	}
}




ESP_LVGL::LVGL& ESP_LVGL::LVGL::GetOrCreateInstance()
{
	singletonMutex.Take();
	if (instance == NULL)
		instance = new LVGL();
	singletonMutex.Give();
	return *instance;
}

