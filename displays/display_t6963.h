#pragma once
#include "display.h"

namespace ESP_LVGL
{

	//Right now all this code contains quite specific stuff for a specific display.
	//This is a todo item. Probably make a settings struct or so.
	//Also the GLCD class should be exp
	
	class DisplayT6963C : public Display
	{
		lv_coord_t width = 0, height = 0;
		T6963C* glcd = NULL;
		uint8_t* buffer = NULL;
		size_t bufferSize = 0;
		lv_disp_draw_buf_t disp_buf;
		lv_disp_drv_t disp_drv;
		lv_disp_t* disp;
		void Flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
		void Round_cb(lv_disp_drv_t * disp_drv, lv_area_t * a);
	public:
		DisplayT6963C(T6963C* glcd);
	};
}
