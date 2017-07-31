#include "pwm.h"

void* update(void* vargsp){
    pwm_t* pin = (pwm_t*)vargsp;
    for(;;){
        if(pin->p->direction == OUT){
            pin->timer++;
            if(pin->timer >= val && pin->p->direction){
                writePin(pin->p, 0);
            }else if(pin->timer < val && !pin->p->direction){
                writePin(pin->p, 1);
            }
            if(pin->timer > 1024){
                pin->timer = 0;
            }
        }else if(pin->p->direction == IN){
            pin->timer++;
            if(!readPin(pin->p)){
                pin->val = pin->timer;
            }
            if(pin->timer > 1024){
                pin->timer = 0;
            }
        }
    }
}

pwm_t* createPWMPin(int pin, int direction){
    pwm_t* pwmpin = (pwm_t*)malloc(sizeof(pwm_t));
    pwmpin->p = createPin(pin, direction);
    pthread_create(pwmpin->tid, NULL, update, (void*)pwmpin);
    return pwmpin;
}

void freePWMPin(pwm_t* pwm){
    freePin(pwm->p);
    pthread_join(pwm->tid);
    free(pwm);
}

int setDirection(pwm_t* pwm, int direction){
    return setDirection(pwm->p, direction);
}

void setValue(pwm_t* pwm, int val){
    pwm->val = val;
}

int readValue(pwm_t* pwm){
    return pwm->val;
}