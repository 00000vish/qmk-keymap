#include "rgb.h"

void initialize_rgb(void) {
   rgb_matrix_mode(RGB_MATRIX_CUSTOM_simple);
}

bool rgb_matrix_indicators_user(void) {
    // Your RGB lighting effects logic here
    return false;
}