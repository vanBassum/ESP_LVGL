#pragma once
#include "esp_system.h"
#include "widget.h"
#include "screen.h"

namespace ESP_LVGL
{
	class Display
	{
		Screen* screen = NULL;
		
	protected:
		lv_disp_t* handle = NULL;
		
	public:

		Screen& GetScreen()
		{
			LVGL::Execute([&]() {
				if(screen == NULL)
					screen = new Screen(lv_disp_get_scr_act(handle));
			});
			
			return *screen;
		}
	};
}
