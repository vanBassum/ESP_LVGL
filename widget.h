#pragma once
#include "esp_system.h"
#include "lvgl.h"

namespace ESP_LVGL
{
	class Widget
	{
	public:
		lv_obj_t* handle = NULL;
				
		~Widget()
		{
			lv_obj_del_async(handle);
		}
		
		virtual esp_err_t Init(Widget& parent) = 0; 
		
	};
}
