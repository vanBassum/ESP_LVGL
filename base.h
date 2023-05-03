#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "lvgl.h"

#include <functional>
#include <type_traits>

#define LVGL_HANDLER_TICK_MS	5	//The timing is not critical but it should be about 5 milliseconds to keep the system responsive.
#define LVGL_TIMER_TICK_MS		1
//#define LVGL_CORE_PROTECTION		//When this is defined, lvgl will throw ESP_LOGE when functions are called from a different core.


namespace ESP_LVGL
{
	class LVGL
	{
		static LVGL _Instance;
		Task  task;
		Timer timer;
		Mutex mutex;
		int coreId = -1;
		
		bool _Init();
		void _Execute(std::function<void()> val);

	public:
		static bool Init() 
		{ 
			return _Instance._Init();
		}
		
		template<typename Function, typename... Arguments>
		static void Execute(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			_Instance._Execute(val);
		}
	};
	
	
}
