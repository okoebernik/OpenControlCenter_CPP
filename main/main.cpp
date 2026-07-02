
#include <cstdio>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"

static const char *TAG = "OCC";

static void occ_create_splash()
{
    lv_obj_t *scr = lv_scr_act();
    lv_obj_clean(scr);

    lv_obj_set_style_bg_color(scr, lv_color_hex(0x1A1A1A), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "OpenControlCenter");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t *sub = lv_label_create(scr);
    lv_label_set_text(sub, "C++17 Foundation v0.1");
    lv_obj_set_style_text_color(sub, lv_color_hex(0x008CFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(sub, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(sub, LV_ALIGN_CENTER, 0, 10);

    lv_obj_t *status = lv_label_create(scr);
    lv_label_set_text(status, "Display + LVGL initialized");
    lv_obj_set_style_text_color(status, lv_color_hex(0x00C853), LV_PART_MAIN);
    lv_obj_set_style_text_font(status, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(status, LV_ALIGN_CENTER, 0, 55);
}

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "OpenControlCenter booting...");
    ESP_LOGI(TAG, "Initializing display");

    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = false,
            .buff_spiram = true,
            .sw_rotate = false,
        }
    };

    lv_display_t *disp = bsp_display_start_with_config(&cfg);
    if (disp == nullptr) {
        ESP_LOGE(TAG, "Display init failed");
        return;
    }

    bsp_display_backlight_on();

    ESP_LOGI(TAG, "Display initialized");
    occ_create_splash();

    while (true) {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}