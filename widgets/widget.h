#pragma once
#include "esp_system.h"
#include "../core/lvglservice.h"

namespace ESP_LVGL
{
	class Widget
	{
	protected:
		std::shared_ptr<LVGLService> lvgl;
		lv_obj_t* handle = NULL;

	public:    
		Widget(std::shared_ptr<LVGLService> lvgl) : lvgl(lvgl) {

		}

		virtual ~Widget() 
		{
			lvgl->ExecuteSafely([&]() 
			{
				lv_obj_del_async(handle);
			});	
		}

		void SetPosition(int x, int y)	
		{ 
			lvgl->ExecuteSafely([&]() 
			{
				lv_obj_set_pos(handle, x, y);
			});	
		}	

		void SetSize(int width, int height)	
		{ 
			lvgl->ExecuteSafely([&]() 
			{
				lv_obj_set_size(handle, width, height);
			});
		}
		
		void SetAlign(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) 
		{ 
			lvgl->ExecuteSafely([&]() 
			{
				lv_obj_align(handle, align, x_ofs, y_ofs);
			});
		}
	};
}

