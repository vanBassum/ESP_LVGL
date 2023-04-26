#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Button : public Widget
	{
		
	public:		
		virtual bool Init(Widget* parent) override
		{
			LVGL::mutex.Take();
			handle = lv_btn_create(parent->handle);
			handle->user_data = this;
			LVGL::mutex.Give();
			return true;
		}
	};
}
