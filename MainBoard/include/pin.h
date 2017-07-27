#ifndef PP_PIN
#define PP_PIN

#define IN 0
#define OUT 1

struct {
    int valID;
    int dirID;
    unsigned int direction : 1;
    char* valBuffer;
    char* dirBuffer;
} pin_t;

int changeDirection(pin_t* pin, int direction);
int readPin(pin_t* pin);
int writePin(pin_t* pin, int val);
pin_t* createPin(int pin, int direction);

#endif