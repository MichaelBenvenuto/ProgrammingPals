#ifndef PP_ESC
#define PP_ESC

#include "pin.h"

struct {
    pwm_t* p;
    double speed;
} esc_t;

esc_t* createSpeedController(int pin);
void freeSpeedController(esc_t* esc);

int setSpeed(esc_t* esc, double speed);

#endif