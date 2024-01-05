#pragma once
#include "esp_system.h"
#include "widget.h"

namespace ESP_LVGL
{
	class Screen : public Widget
	{
	public:
		Screen(std::shared_ptr<LVGLService> lvgl) : Widget(lvgl)
		{
			lvgl->ExecuteSafely([&]() {
				handle = lv_obj_create(NULL, NULL);
			});
		}
	};
}
