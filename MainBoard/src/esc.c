#include "esc.h"

esc_t* createSpeedController(int pin){
    esc_t* speedController = (esc_t*)malloc(sizeof(esc_t));
    speedController.p = createPin(pin, OUT);
}

void freeSpeedController(esc_t* esc){
    freePin(esc.p);
    free(esc);
}

int setSpeed(esc_t* esc, double speed){
    p.speed = speed;
}