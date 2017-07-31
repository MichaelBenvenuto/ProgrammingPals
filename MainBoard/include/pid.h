#ifndef PP_PID
#define PP_PID

#include <pthread.h>

struct{
    unsigned double p, i, d;
    double setpoint;
    double input, output;
    double error, perror;
    pthread_t* tid;
} pid_t;

pid_t* createPID(double p, double i, double d);

double getOutput(pid_t* pid);

#endif