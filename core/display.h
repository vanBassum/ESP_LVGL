#pragma once
#include "lvgl/lvgl.h"
#include "esp_system.h"
#include "widget.h"
#include "screen.h"


namespace ESP_LVGL
{
	class Display
	{
		Screen* screen = NULL;
		
	protected:
		struct _lv_display_t* handle = NULL;
		
	public:

		~Display()
		{
			delete screen; // Release the memory for the screen object
		}

		Screen& GetScreen()
		{
			LVGL::ExecuteSafely([&]() {
				if(screen == NULL)
					screen = new Screen(lv_disp_get_scr_act(handle));
			});
			
			return *screen;
		}
	};
}
