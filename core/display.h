#pragma once
#include "lvgl/lvgl.h"
#include "esp_system.h"
#include "widget.h"
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

		static void staticFlushCallback(struct _lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
			Display *instance = static_cast<Display *>(disp->user_data);
			instance->flushCallback(disp, area, px_map);
		}

	public:
		Display(std::shared_ptr<LVGLService> lvgl) : lvgl(std::move(lvgl)) {
			assert(this->lvgl);
		}

		virtual ~Display() {
			// Ensure resources are released
			if (disp_buf) {
				disp_buf.reset();
			}
		}

		void setConfig(const Config &newConfig) {
			assert(!initialized);
			config = newConfig;
		}

		void init() {
			assert(!initialized);

			disp_buf = std::make_unique<uint8_t[]>(config.bufferSize);
			assert(disp_buf);

			lvgl->executeSafely([&]() {
				// Create a display and set a flush_cb
				handle = lv_display_create(config.width, config.height);
				lv_display_set_flush_cb(handle, staticFlushCallback);
				lv_display_set_draw_buffers(handle, disp_buf.get(), nullptr, config.bufferSize, LV_DISPLAY_RENDER_MODE_PARTIAL);
			});

			handle->user_data = this;
			initialized = true;
		}

		void showScreen(std::shared_ptr<Screen> screen) {
			assert(initialized && screen);
			lvgl->executeSafely([&]() {
				lv_disp_load_scr(handle, screen->getHandle());
			});
		}
	};
}
