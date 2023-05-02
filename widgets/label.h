#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Label : public Widget
	{
	public:
		bool Init(Widget* parent)
		{
			auto lambda = [](Widget* _parent, lv_obj_t** _handle) 
			{
				*_handle = lv_label_create(_parent->handle);
			};
			InitSafely(lambda, parent, &handle);
			SetPosition(0, 0);
			SetText("New label");
			return handle != NULL;
		}
				
		void SetText(std::string text)
		{
			RunSafely(lv_label_set_text, handle, text.c_str());
		}
		
		template<typename ...Args>
		void SetText(std::string text, Args... args)
		{
			RunSafely(lv_label_set_text_fmt, handle, text.c_str(), args...);
		}
		
		void SetLongMode(lv_label_long_mode_t mode)
		{
			RunSafely(lv_label_set_long_mode, handle, mode);
		}
	};
}