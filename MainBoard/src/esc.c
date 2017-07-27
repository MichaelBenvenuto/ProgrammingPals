#include "esc.h"

esc_t* createSpeedController(int pin){
    esc_t* speedController = (esc_t*)malloc(sizeof(esc_t));
    speedController.p = createPin(pin, OUT);
}

void freeSpeedController(esc_t* esc){
    freePWMPin(esc.p);
    free(esc);
}

int setSpeed(esc_t* esc, double speed){
    if(esc){
        esc.speed = speed;
        setValue(esc->p, (int)(speed * 1024.0f));
    }else{
        return 0;
    }
    return 1;
}