#pragma once
#include "esp_system.h"
#include "lvgl.h"
#include "base.h"

namespace ESP_LVGL
{
	class Widget
	{
	public:
		lv_obj_t* handle = NULL;
				
		~Widget()
		{
			if (handle != NULL)
				lv_obj_del_async(handle);
		}
		
		virtual bool Init(Widget* parent) = 0; 
		
		void SetPosition(int x, int y)
		{
			if (handle == NULL)
				return;
			LVGL::mutex.Take();
			lv_obj_set_pos(handle, x, y);  
			LVGL::mutex.Give();
			
		}
		
		void SetSize(int width, int height)
		{
			if (handle == NULL)
				return;
			LVGL::mutex.Take();
			lv_obj_set_size(handle, width, height);
			LVGL::mutex.Give();
		}
		
		void SetAlign(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
		{
			lv_obj_align(handle, align, x_ofs, y_ofs);
		}
	};
}
