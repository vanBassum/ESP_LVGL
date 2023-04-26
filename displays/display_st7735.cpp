#include "display_st7735.h"


bool ESP_LVGL::DisplayST7735::Init(ST7735* glcd)
{
	this->glcd = glcd;
	if (glcd == NULL)
		return false;
			
	width = glcd->settings.width;
	height = glcd->settings.width;
			
	bufferSize = width * 10;
	buffer = (uint8_t*)malloc(bufferSize);
	if (buffer == NULL)
		return false;
			
	lv_disp_draw_buf_init(&disp_buf, buffer, NULL, bufferSize);
	lv_disp_drv_init(&disp_drv);			
	disp_drv.draw_buf = &disp_buf;			
	disp_drv.hor_res = width;
	disp_drv.ver_res = height;
	disp_drv.user_data = this;
	disp_drv.flush_cb = [](lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
		DisplayST7735* instance = (DisplayST7735*)disp_drv->user_data;
		instance->Flush_cb(disp_drv, area, color_p);
		lv_disp_flush_ready(disp_drv);
	};
	
	////Always write complete lines.
	//disp_drv.rounder_cb = [](lv_disp_drv_t * disp_drv, lv_area_t * a) {	
	//	DisplayST7735* instance = (DisplayST7735*)disp_drv->user_data;
	//	instance->Round_cb(disp_drv, a);
	//	lv_disp_flush_ready(disp_drv);
	//};
	
	//disp_drv.set_px_cb = [](struct _lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa) {
	// https://maldus512.medium.com/porting-littlevgl-for-a-monochrome-display-6c7be58851ce
	// Not required
	//};

	disp = lv_disp_drv_register(&disp_drv); 
	return true;
}


void ESP_LVGL::DisplayST7735::Flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	if (glcd == NULL)
		return;
	
	size_t width = area->x2 - area->x1 + 1;
	size_t height = area->y2 - area->y1 + 1;
	size_t pixels = width * height;
	glcd->SetWindow(area->x1, area->y1, area->x2, area->y2);
	glcd->WriteWindow((uint16_t*)color_p, pixels);
}


void ESP_LVGL::DisplayST7735::Round_cb(lv_disp_drv_t * disp_drv, lv_area_t * area)
{
	area->x1 = 0;
	area->x2 = glcd->settings.width;
	area->y2 = area->y1;
}



