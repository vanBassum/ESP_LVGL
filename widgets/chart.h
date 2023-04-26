#pragma once
#include <string>
#include "widget.h"

namespace ESP_LVGL
{
	class Chart : public Widget
	{
	public:		
		virtual bool Init(Widget* parent) override
		{
			LVGL::mutex.Take();
			handle = lv_chart_create(parent->handle);
			handle->user_data = this;
			LVGL::mutex.Give();
			return true;
		}
		
		void SetType(lv_chart_type_t type)
		{
			LVGL::mutex.Take();
			lv_chart_set_type(handle, type);
			LVGL::mutex.Give();
		}
		
		void SetPointCount(uint16_t cnt)
		{
			LVGL::mutex.Take();
			lv_chart_set_point_count(handle, cnt);
			LVGL::mutex.Give();
		}
		
		void SetRange(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max)
		{
			lv_chart_set_range(handle, axis, min, max);
		}
	};
	
	
	class ChartSeries
	{
		Chart* parent = NULL;
		lv_chart_series_t* handle = NULL;
	public:		
		bool Init(Chart* parent, lv_color_t color, lv_chart_axis_t axis)
		{
			LVGL::mutex.Take();
			this->parent = parent;
			handle = lv_chart_add_series(parent->handle, color, axis);
			LVGL::mutex.Give();
			return true;
		}
		
		void SetYArray(lv_coord_t* points)
		{
			LVGL::mutex.Take();
			lv_chart_set_ext_y_array(parent->handle, handle, points);
			LVGL::mutex.Give();
			
		}
	};
	
}