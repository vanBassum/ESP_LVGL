#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "esp_log.h"
#include "lvgl.h"
#include <functional>
#include <type_traits>

#define LVGL_HANDLER_TICK_MS	5	//The timing is not critical but it should be about 5 milliseconds to keep the system responsive.
#define LVGL_TIMER_TICK_MS		1

namespace ESP_LVGL
{
	class LVGL
	{
		const char* TAG = "LVGL";
		static Mutex singletonMutex;
		static LVGL* instance;

		int coreId = -1;
		Task task;
		Timer timer;	
		Mutex mutex;
		
		void Work(Task* task, void* args);
		
		void _Execute(std::function<void()> function)							//Function to execute lvgl commands in a safe manner.
		{
			bool coreMatch = false;
			mutex.Take();
			coreMatch = coreId == Task::GetCurrentCoreID();
			if (coreMatch)
			{
				function();				
			}
			else
			{
				ESP_LOGE(TAG, "Called LVGL function from wrong core. Use core %d", coreId);
			}
			mutex.Give();		
		}
		
	protected:
		LVGL();
		
	public:
		LVGL(LVGL &other) = delete;										//Singletons should not be cloneable.
		void operator=(const LVGL &) = delete;							//Singletons should not be assignable.
		static LVGL& GetOrCreateInstance();								//Returns instance, if NULL it will be created.
		static void Execute(std::function<void()> function)
		{
			return GetOrCreateInstance()._Execute(function);
		}

	};
}

