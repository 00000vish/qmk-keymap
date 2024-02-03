
#include "oled.h"
#include "ssd1306.h"

#define OLED_ROTATION_DEFAULT OLED_ROTATION_0

oled_rotation_t rotation = OLED_ROTATION_DEFAULT;

void oled_init(void) {
    ssd1306_init();
    ssd1306_set_rotation(rotation);
    ssd1306_clear();
}

void oled_task(void) {
}

void oled_write_P(const char *data, bool center) {
}

void oled_draw_smiley(void) {
    ssd1306_draw_pixel(80, 16, 1);
    ssd1306_draw_pixel(48, 16, 1);
    ssd1306_draw_circle(64, 32, 24, 1);
}
