#include "pid.h"

#include <stdlib.h>
#include <time.h>

void* update(void* vargs){
    pid_t** pid = (pid_t**)vargs;
    *pid->perror = 0;
    *pid->output = 0;
    double integral = 0;
    clock_t startTime;
    clock_t dt = 1;
    for(;;){
        startTime = clock();
        *pid->error = *pid->setpoint - *pid->input;
        integral += *pid->output + (*pid->error * dt);
        double derivative = (*pid->error - *pid->perror)/dt;
        *pid->output = (*pid->p * *pid->error) + (*pid->i * integral) + (*pid->d * derivative);
        *pid->perror = *pid->error;
        dt = (double)(clock() - startTime) / CLOCKS_PER_SECOND;
    }
}

pid_t* createPID(double p, double i, double d){
    pid_t* pid = (pid_t*)malloc(sizeof(pid_t));
    pid->p = p;
    pid->i = i;
    pid->d = d;

    pthread_create(pid->tid, NULL, update, &pid);
    return pid;
}

void freePID(pid_t* pid){
    pthread_join(pid->tid);
    free(pid);
}