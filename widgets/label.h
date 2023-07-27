#pragma once
#include "esp_system.h"
#include "widget.h"

namespace ESP_LVGL
{
	class Label : public Widget
	{
	public:
		Label(Widget& parent)
		{
			LVGL::Execute([&]() {
				handle = lv_label_create(parent.handle);
			});
		}
		
		void SetText(std::string text)
		{
			LVGL::Execute([&]() {
				lv_label_set_text(handle, text.c_str());
			});
		}
		
		template<typename ...Args>
		void SetText(std::string text, Args... args)
		{
			LVGL::Execute([&]() {
				lv_label_set_text_fmt(handle, text.c_str(), args...);
			});
		}
		
		void SetLongMode(lv_label_long_mode_t mode)
		{
			LVGL::Execute([&]() {
				lv_label_set_long_mode(handle, mode);
			});
		}
		
	};
}
