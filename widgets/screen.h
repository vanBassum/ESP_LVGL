#pragma once
#include "widget.h"
#include "display.h"
#include "esp_drivers.h"

namespace ESP_LVGL
{
	class Screen : public Widget
	{
	public:
		
		bool Init()
		{
			handle = lv_scr_act();
			return true;
		}
		
		bool Init(Display* display)
		{
			//TODO:
			//handle = ...
			//return ESP_OK;
			return false;
		}
		
		virtual bool Init(Widget* parent) override
		{
			return true;
		}
	};
}
