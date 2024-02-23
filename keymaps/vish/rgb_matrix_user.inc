RGB_MATRIX_EFFECT(simple)
RGB_MATRIX_EFFECT(cycle)
RGB_MATRIX_EFFECT(breathe)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "rgb/effects/simple.c"
#include "rgb/effects/cycle.c"
#include "rgb/effects/breathe.c"
#endif
