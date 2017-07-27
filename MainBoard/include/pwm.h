#ifndef PP_PWM
#define PP_PWM

#include <pthread.h>

#include "pin.h"

struct {
    pin_t* p;
    int val;
    pthread_t* tid;
    int timer;
} pwm_t;

pwm_t* createPWMPin(int pin, int direction);
void freePWMPin(pwm_t* pwm);

void setValue(pwm_t* pwm, int speed);
int readValue(pwm_t* pwm);

#endif