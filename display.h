#pragma once
#include "esp_system.h"
#include "widget.h"

namespace ESP_LVGL
{

	class Display
	{
	public:
		virtual esp_err_t Register() = 0;
		
	};
}