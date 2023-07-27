#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "lvgl.h"

#include <functional>
#include <type_traits>

#define LVGL_HANDLER_TICK_MS	5	//The timing is not critical but it should be about 5 milliseconds to keep the system responsive.
#define LVGL_TIMER_TICK_MS		1

namespace ESP_LVGL
{
	class LVGL
	{
		static LVGL _Instance;
		Task task;
		Timer timer;
		Mutex mutex;
		int coreId = -1;
		bool coreProtection = true;
		
		void _Execute(std::function<void()> val);
		void _Work(Task* task, void* args);
		void _Start();
		
		
	public:

		static void Init() 
		{ 
			lv_init();
			_Instance._Start();
		}
		
		
		template<typename Function, typename... Arguments>
		static void Execute(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			_Instance._Execute(val);
		}
		
		static void SetCoreProtection(bool enabled)
		{
			_Instance.coreProtection = enabled;
		}
	};
}
