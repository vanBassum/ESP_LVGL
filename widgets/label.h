#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Label : public Widget
	{
		
	public:		
		virtual esp_err_t Init(Widget* parent) override
		{
			LVGL::mutex.Take();
			handle = lv_label_create(parent->handle);
			handle->user_data = this;
			lv_label_set_text(handle, "Label");
			lv_obj_set_pos(handle, 0, 0);
			LVGL::mutex.Give();
			return ESP_OK;
		}

		
		void SetText(std::string text)
		{
			if (handle == NULL)
				return;
			LVGL::mutex.Take();
			lv_label_set_text(handle, text.c_str());
			LVGL::mutex.Give();
		}
		
		template<typename ...Args>
		void SetText(std::string text, Args... args)
		{
			if (handle == NULL)
				return;
			LVGL::mutex.Take();
			lv_label_set_text_fmt(handle, text.c_str(), args...);
			LVGL::mutex.Give();
		}
		
		
		
	};
}