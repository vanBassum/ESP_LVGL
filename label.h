#pragma once
#include <string>
#include "widget.h"
#include "base.h"

namespace ESP_LVGL
{
	class Label : public Widget
	{
		
	public:		

		
		void SetText(std::string text)
		{
			lv_label_set_text(handle, text.c_str());
		}
		
		template<typename ...Args>
		void SetText(std::string text, Args... args)
		{
			lv_label_set_text_fmt(handle, text.c_str(), args...);
		}
		
		
		virtual esp_err_t Init(Widget& parent) override
		{
			LVGL::mutex.Take();
			handle = lv_label_create(parent.handle);
			lv_label_set_text(handle, "Label");    
			lv_obj_set_size(handle, 120, 50);
			LVGL::mutex.Give();
			return ESP_OK;
		}
	};
}