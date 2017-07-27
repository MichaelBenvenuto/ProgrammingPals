#include "pin.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int export = 0;
int unexport = 0;

int pinBufSize = 0;
int* pins = 0;

int pinExists(int pin){
    if(pins){
        for(int i = 0; i < pinBufSize; i++){
            if(pins[i] == pin){
                return 1;
            }
        }
    }
    return 0;
}


int nLength(int x){
    int c;
    int n = x;
    for(c = 0; n != 0; c++, n /= 10);
    return c;
}

void freePin(pin_t* pin){
    close(pin.dirID);
    close(pin.valID);
    free(pin.dirBuffer);
    free(pin.valBuffer);
    free(pin);
}


int changeDirection(pin_t* pin, int direction){
    int err;
    if(direction == OUT){
        err = write(dir, "out", 3);
    }else if(direction == IN){
        err = write(dir, "in", 2);
    }else{
        return -1;
    }

    pin.direction = direction;

    return err;
}


int readPin(pin_t* pin){
    char c;
    int err = read(pin.id, &c, sizeof(char));
    if(err < 0){
        return -1;
    }
    return atoi(&c);
}


int writePin(pin_t* pin, int val){
    char c;
    sprintf(&c, "%i", val);
    return write(pin.id, &c);
}


pin_t* createPin(int pin, int direction){

    if(!export){
        export = open("/sys/class/gpio/export", O_WRONLY);
    }
    if(!unexport){
        unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    }

    int pinSize = nLength(pin);

    if((export > 0 && unexport > 0) && !pinExists(pin)){

        char* pinChar = (char*)malloc(pinSize * sizeof(char));
        sprintf(pinChar, "%i", pin);

        write(export, pinChar, pinSize);

        pin_t* pin = (pin_t*)malloc(sizeof(pin_t));
    
        pin.valBuffer = (char*)malloc((26 + pinSize) * sizeof(char));
        sprintf(pin.valBuffer, "/sys/class/gpio/gpio%s/value", pinChar);

        pin.dirBuffer = (char*)malloc((30 + pinSize) * sizeof(char));
        sprintf(pin.dirBuffer, "/sys/class/gpio/gpio%s/direction", pinChar);

        pin.valID = open(pin.buffer, O_RDWR | O_TRUNC);
        pin.dirID = open(pin.dirBuffer, O_RDWR | O_TRUNC);
        
        if(direction == OUT){
            write(dir, "out", 3);
        }else if(direction == IN){
            write(dir, "in", 2);
        }else{
            return -1;
        }
        close(dir);
        pin.direction = direction;

        pinBufSize++;
        pins = (int*)realloc(pins, pinBufSize * sizeof(int));
        pins[pinBufSize - 1] = pin;

        return pin;

    }else{
        return 0;
    }
}