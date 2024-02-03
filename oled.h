#pragma once

#include "quantum.h"

void oled_init(void);
void oled_task(void);
void oled_write_P(const char *data, bool center);
void oled_draw_smiley(void);
