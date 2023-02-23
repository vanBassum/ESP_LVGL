#pragma once
#include "widget.h"
#include "display.h"
#include "esp_drivers.h"

namespace ESP_LVGL
{
	class Screen : public Widget
	{
	public:
		
		esp_err_t Init()
		{
			handle = lv_scr_act();
			return ESP_OK;
		}
		
		esp_err_t Init(Display& display)
		{
			//TODO:
			//handle = ...
			//return ESP_OK;
			return ESP_FAIL;
		}
		
		virtual esp_err_t Init(Widget& parent) override
		{
			return ESP_FAIL;
		}
	};
}
