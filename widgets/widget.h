#pragma once
#include "esp_system.h"
#include "lvgl.h"
#include "base.h"


namespace ESP_LVGL
{
	class Widget
	{
	protected:
		template<typename Function, typename... Arguments>
		void RunSafely(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			auto lambda = [](std::function<void()> _val, lv_obj_t* handle) 
			{
				if (handle != NULL)
				{
					_val();
				}
			};
			
			LVGL::Execute(lambda, val, handle);
		}	
		
		template<typename Function, typename... Arguments>
		void InitSafely(Function func, Arguments... parameters)
		{
			std::function<void()> val{std::bind(func, parameters...)};
			auto lambda = [](std::function<void()> _val, lv_obj_t* _handle, Widget* _this) 
			{
				if (_handle == NULL)
				{
					_val();
					if (_handle != NULL)
						_handle->user_data = _this;
				}
			};
			
			LVGL::Execute(lambda, val, handle, this);
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
