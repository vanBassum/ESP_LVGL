#pragma once
#include "esp_system.h"
#include <memory>
#include "../core/lvglservice.h"

namespace ESP_LVGL
{
	class Widget
	{
	protected:


	public:    
		std::shared_ptr<LVGLService> lvgl;
		lv_obj_t* handle = NULL;

		Widget(std::shared_ptr<LVGLService> lvgl) : lvgl(lvgl) {

		}

		virtual ~Widget() 
		{
			lvgl->executeSafely([&]() 
			{
				lv_obj_del_async(handle);
			});	
		}

		void SetPosition(int x, int y)	
		{ 
			lvgl->executeSafely([&]() 
			{
				lv_obj_set_pos(handle, x, y);
			});	
		}	

		void SetSize(int width, int height)	
		{ 
			lvgl->executeSafely([&]() 
			{
				lv_obj_set_size(handle, width, height);
			});
		}
		
		void SetAlign(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) 
		{ 
			lvgl->executeSafely([&]() 
			{
				lv_obj_align(handle, align, x_ofs, y_ofs);
			});
		}
	};
}

