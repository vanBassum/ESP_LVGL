#include "lvgl/lvgl.h"
#include "display.h"
#include "lvgl/src/display/lv_display_private.h"


void ESP_LVGL::Display::staticFlushCallback(struct _lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    Display *instance = static_cast<Display *>(disp->user_data);
    instance->flushCallback(disp, area, px_map);
}


ESP_LVGL::Display::Display(std::shared_ptr<LVGLService> lvgl) : lvgl(std::move(lvgl)) {
    assert(this->lvgl);
}

ESP_LVGL::Display::~Display() {
    // Ensure resources are released
    if (disp_buf) {
        disp_buf.reset();
    }
}

void ESP_LVGL::Display::setConfig(const Config &newConfig) {
    assert(!initialized);
    config = newConfig;
}

void ESP_LVGL::Display::init() {
    assert(!initialized);

    disp_buf = std::make_unique<uint8_t[]>(config.bufferSize);
    assert(disp_buf);

    lvgl->executeSafely([&]() {
        // Create a display and set a flush_cb
        handle = lv_display_create(config.width, config.height);
        lv_display_set_flush_cb(handle, staticFlushCallback);
        //lv_display_set_draw_buffers(handle, disp_buf.get(), nullptr, config.bufferSize, LV_DISPLAY_RENDER_MODE_PARTIAL);
    });

    handle->user_data = this;
    initialized = true;
}

void ESP_LVGL::Display::showScreen(Screen& screen) {
    assert(initialized);
    lvgl->executeSafely([&]() {
        lv_disp_load_scr(screen.handle);
    });
}