#include "mlvgl.h"

Mutex ESP_LVGL::LVGL::singletonMutex;
ESP_LVGL::LVGL* ESP_LVGL::LVGL::instance {NULL};

ESP_LVGL::LVGL::LVGL()
{
	lv_init();
	
	static TaskHandle_t handle;
	xTaskCreatePinnedToCore([](void* args){((ESP_LVGL::LVGL*)args)->Work(NULL, NULL);}, "test", 2048*4, this, 2, &handle, 0);
	
	//task.Init("LVGL", 2, 2048 * 4);
	//task.Bind(this, &ESP_LVGL::LVGL::Work);
	//task.RunPinned(1);
			
	timer.Init("LVGL", TimeSpan(LVGL_TIMER_TICK_MS));
	timer.Bind([](Timer* t) { lv_tick_inc(t->GetPeriod().GetMiliSeconds()); });
	timer.Start();
}



void ESP_LVGL::LVGL::Work(Task* task, void* args)
{
	mutex.Take("GetCurrentCoreID");
	coreId = Task::GetCurrentCoreID();	//Note the coreId.
	mutex.Give();
	ESP_LOGE(TAG, "LVGL running on core %d", coreId);
	while (1)
	{
		if (mutex.Take("LVGL Work", pdMS_TO_TICKS(1000)))
		{
			lv_timer_handler();
			mutex.Give();
		}
		else
			ESP_LOGE(TAG, "Mutex in Work");
		
		vTaskDelay(pdMS_TO_TICKS(LVGL_HANDLER_TICK_MS));
	}
}


void ESP_LVGL::LVGL::ExecuteSafely(std::function<void()> function, const char* d)
{
	return GetOrCreateInstance().Execute(function, d);
}


void ESP_LVGL::LVGL::Execute(std::function<void()> function, const char* d)
{
	if (mutex.Take(d, pdMS_TO_TICKS(1000)))
	{
		if (coreId != Task::GetCurrentCoreID())
			ESP_LOGE(TAG, "Called LVGL function from wrong core. Use core %d", coreId);
		function();	
		mutex.Give();		
	}
	else
		ESP_LOGE(TAG, "Mutex in Execute");
	
}



ESP_LVGL::LVGL& ESP_LVGL::LVGL::GetOrCreateInstance()
{
	singletonMutex.Take();
	if (instance == NULL)
		instance = new LVGL();
	singletonMutex.Give();
	return *instance;
}

