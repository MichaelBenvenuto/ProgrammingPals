#include "pwm.h"

void* update(void* vargsp){
    pwm_t* pin = (pwm_t*)vargsp;
    pin.timer++;
    if(pin.timer >= val && pin->p->direction){
        writePin(pin, 0);
    }else if(pin.timer < val && !pin->p->direction){
        writePin(pin, 1);
    }
    if(pin.timer > 1024){
        pin.timer = 0;
    }
}

pwm_t* createPWMPin(int pin){
    pwm_t* pin = (pwm_t*)malloc(sizeof(pwm_t));
    pin->p = createPin(pin, OUT);
    pthread_create(pin.tid, NULL, update, (void*)pin);
    return pin;
}

void freePWMPin(pwm_t* pwm){
    freePin(pwm.p);
    pthread_join(pwm.tid);
    free(pwm);
}

void setValue(pwm_t* pwm, int val){
    pwm.val = val;
}