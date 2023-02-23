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
		GLCD* glcd = NULL;
		uint8_t* buffer = NULL;
		size_t bufferSize = 0;
		lv_disp_draw_buf_t disp_buf;
		lv_disp_drv_t disp_drv;
		lv_disp_t* disp;
		
		void Flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
		{
			if (glcd == NULL)
				return;
			int32_t x, y;
			//Rounder ensures a whole line always needs to be updated.
			uint8_t buf[30];	//30 columns
			for (y = area->y1; y <= area->y2; y++) 
			{
				for (x = area->x1; x <= area->x2; x++)
				{
					bool color = lv_color_brightness(*color_p) < 128;
					uint8_t col = x >> 3;
					uint8_t pixel = x & 0x07;
					uint8_t mask = 1 << (7 - pixel);
					if (color) {
						buf[col] |= mask;
					}
					else {
						buf[col] &= ~mask;
					}
					color_p++;
				}
				glcd->WriteRow(y, buf, 30);
			}
		}
	public:
		esp_err_t Init(GLCD* glcd)
		{
			if (glcd == NULL)
				return ESP_FAIL;
			this->glcd = glcd;
			
			uint32_t width = glcd->GetWidth();
			uint32_t height = glcd->GetHeight();
			
			bufferSize = width * 10;
			buffer = (uint8_t*)malloc(bufferSize);
			if (buffer == NULL)
				return ESP_FAIL;
			
			lv_disp_draw_buf_init(&disp_buf, buffer, NULL, bufferSize);
			lv_disp_drv_init(&disp_drv);			
			disp_drv.draw_buf = &disp_buf;			
			disp_drv.hor_res = width;
			disp_drv.ver_res = height;
			disp_drv.user_data = this;
			disp_drv.flush_cb = [](lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
				Display* instance = (Display*)disp_drv->user_data;
				instance->Flush_cb(disp_drv, area, color_p);
				lv_disp_flush_ready(disp_drv);
			};
	
			//Always write complete lines.
			disp_drv.rounder_cb = [](struct _lv_disp_drv_t * disp_drv, lv_area_t * a) {	
				a->x1 = 0;
				a->x2 = 240;	
			};
	
			//disp_drv.set_px_cb = [](struct _lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa) {
			// https://maldus512.medium.com/porting-littlevgl-for-a-monochrome-display-6c7be58851ce
			// Not required
			//};

			disp = lv_disp_drv_register(&disp_drv); 
			return ESP_OK;
		}
		
		
		
		
		
	};
}