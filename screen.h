#pragma once
#include "widget.h"
#include "display.h"

namespace ESP_LVGL
{
	class Screen : public Widget
	{
	public:
		
		esp_err_t Init(Display& display)
		{
			handle = lv_scr_act();
			return ESP_OK;
		}
		
		virtual esp_err_t Init(Widget& parent) override
		{
			handle = lv_scr_act();
			return ESP_OK;
		}
	};
}
