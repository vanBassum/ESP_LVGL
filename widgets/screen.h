#pragma once
#include "widget.h"
#include "iglcd.h"
#include "esp_drivers.h"

namespace ESP_LVGL
{
	class Screen : public Widget
	{

	public:
		
		bool Init()
		{
			auto lambda = [](lv_obj_t** _handle) 
			{
				*_handle = lv_scr_act();
			};
			InitSafely(lambda, &handle);
			return handle != NULL;
		}
		
		bool Init(IGLCD* display)
		{
			//auto lambda = [](lv_obj_t* _handle)	TODO
			//{
			//	_handle = lv_scr_act();
			//};
			//InitSafely(lambda, handle);
			return false;
		}
	};
}
