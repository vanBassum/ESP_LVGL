#pragma once
#include "esp_system.h"
#include "widget.h"
#include "esp_drivers.h"

using namespace ESP_Drivers;

namespace ESP_LVGL
{

	//Right now all this code contains quite specific stuff for a specific display.
	//This is a todo item. Probably make a settings struct or so.
	//Also the GLCD class should be exp
	
	class Display
	{
		GLCD_Mono* glcdMono = NULL;
		uint8_t* buffer = NULL;
		size_t bufferSize = 0;
		lv_disp_draw_buf_t disp_buf;
		lv_disp_drv_t disp_drv;
		lv_disp_t* disp;
		void Flush_cb_mono(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
	public:
		esp_err_t Init(GLCD_Mono* glcdMonochrome);
		
		
		
		
		
	};
}