#pragma once
#include "esp_system.h"
#include "lvgl.h"
#include "base.h"
#include <functional>
#include <type_traits>

namespace ESP_LVGL
{
	class Widget
	{
	protected:
		template<typename Function, typename... Arguments>
		void RunSafely(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			LVGL::mutex.Take();
			if (handle != NULL)
			{
				val();
				if(handle != NULL)
					handle->user_data = this;
			}
			LVGL::mutex.Give();
		}	
		
		template<typename Function, typename... Arguments>
		void InitSafely(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			LVGL::mutex.Take();
			val();
			LVGL::mutex.Give();
		}	
		
	public:
		lv_obj_t* handle = NULL;
		~Widget()
		{
			auto lambda = [](lv_obj_t* _handle) 
			{
				lv_obj_del_async(_handle);
			};
			RunSafely(lambda, handle);
		}
	
		void SetPosition(int x, int y)	{ RunSafely(lv_obj_set_pos, handle, x, y); }		
		void SetSize(int width, int height)	{ RunSafely(lv_obj_set_size, handle, width, height); }
		void SetAlign(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) { RunSafely(lv_obj_align, handle, align, x_ofs, y_ofs); }
		

	};
}
