#ifndef PP_NETWORKING
#define PP_NETWORKING

#include <pthread.h>
#include <sys/socket.h>

struct{
    pthread_t* tid;
    int id;
    int port;
    struct sockaddr_in* socket;
} net_t;

int init_net();

net_t* createNetSocket(int port);
void freeNetSocket(net_t* sock);

#endif