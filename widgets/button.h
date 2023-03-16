#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Button : public Widget
	{
		
	public:		
		virtual esp_err_t Init(Widget* parent) override
		{
			LVGL::mutex.Take();
			handle = lv_btn_create(parent->handle);
			handle->user_data = this;
			LVGL::mutex.Give();
			return ESP_OK;
		}
	};
}
