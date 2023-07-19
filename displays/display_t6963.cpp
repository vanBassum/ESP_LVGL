#include "display_t6963.h"


ESP_LVGL::DisplayT6963C::DisplayT6963C(T6963C& glcd)
	: glcd(glcd)
{
			
	width = glcd.settings.width;
	height = glcd.settings.width;
			
	bufferSize = width * 10;
	buffer = (uint8_t*)malloc(bufferSize);
	if (buffer != NULL)
	{
		lv_disp_draw_buf_init(&disp_buf, buffer, NULL, bufferSize);
		lv_disp_drv_init(&disp_drv);			
		disp_drv.draw_buf = &disp_buf;			
		disp_drv.hor_res = width;
		disp_drv.ver_res = height;
		disp_drv.user_data = this;
		disp_drv.flush_cb = [](lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
			DisplayT6963C* instance = (DisplayT6963C*)disp_drv->user_data;
			instance->Flush_cb(disp_drv, area, color_p);
			lv_disp_flush_ready(disp_drv);
		};
	
		//Always write complete lines.
		disp_drv.rounder_cb = [](lv_disp_drv_t * disp_drv, lv_area_t * a) {	
			DisplayT6963C* instance = (DisplayT6963C*)disp_drv->user_data;
			instance->Round_cb(disp_drv, a);
			lv_disp_flush_ready(disp_drv);
		};
	
		//disp_drv.set_px_cb = [](struct _lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa) {
		// https://maldus512.medium.com/porting-littlevgl-for-a-monochrome-display-6c7be58851ce
		// Not required
		//};

		disp = lv_disp_drv_register(&disp_drv); 
	}
}

void ESP_LVGL::DisplayT6963C::Round_cb(lv_disp_drv_t * disp_drv, lv_area_t * a)
{
	a->x1 = 0;
	a->x2 = width;	
}

void ESP_LVGL::DisplayT6963C::Flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
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
		glcd.WriteRow(y, buf, 30);
	}
}






