#pragma once
#include "lvgl/lvgl.h"
#include "esp_system.h"
#include "screen.h"



namespace ESP_LVGL
{
	class Display {
	public:
		struct Config {
			lv_coord_t width = 0;
			lv_coord_t height = 0;
			size_t bufferSize = 0;
		};

	protected:
		virtual void flushCallback(struct _lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) = 0;

	private:
		std::shared_ptr<LVGLService> lvgl;
		struct _lv_display_t *handle = nullptr;
		std::unique_ptr<uint8_t[]> disp_buf;
		bool initialized = false;
		Config config = {};

		static void staticFlushCallback(struct _lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

	public:
		Display(std::shared_ptr<LVGLService> lvgl);
		virtual ~Display();
		void setConfig(const Config &newConfig);
		void init();
		void showScreen(Screen& screen);
	};
}
