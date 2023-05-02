#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Button : public Widget
	{
	public:
		bool Init(Widget* parent)
		{
			auto lambda = [](Widget* _parent, lv_obj_t** _handle) 
			{
				*_handle = lv_btn_create(_parent->handle);
			};
			InitSafely(lambda, parent, &handle);
			return handle != NULL;
		}


	};
}


