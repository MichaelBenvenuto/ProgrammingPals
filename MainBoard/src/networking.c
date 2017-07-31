#include "networking.h"
#include "numbers.h"

#include <stdlib.h>
#include <arpa/inet.h>

int sockSize = 0;
int* usedSockets = 0;
net_t* mainSocket = 0;

void* update(void* vargsp){

}

int init_net(){
    mainSocket = (net_t*)malloc(sizeof(net_t));
    pthread_create(mainSocket->id, NULL, update, NULL);
    mainSocket->id = socket(AF_INET, SOCK_STREAM, 0);

    mainSocket->socket.sin_addr.s_addr = af_inet("127.0.0.1")
    mainSocket->socket.sin_family = AF_INET;
    mainSocket->socket.sin_port = htons(88);

    if(connect(mainSocket->id, (struct sockaddr*)&mainSocket->socket, sizeof(mainSocket->socket)) < 0){
        return 0;
    }

    int* old = usedSockets;
    sockSize++;
    usedSockets = (int*)realloc(usedSockets, sockSize * sizeof(int));
    if(old != usedSockets){
        free(old);
    }
    usedSockets[sockSize - 1] = 88;
    return 1;
}

net_t* createNetSocket(int port){}

    if(!mainSocket){
        if(!init_net()){
            return 0;
        }
    }

    for(int i = 0; i < sockSize && usedSockets != 0; i++){
        if(usedSockets[i] == port){
            return 0;
        }
    }

    net_t* sock = (net_t*)malloc(sizeof(net_t));
    pthread_create(mainSocket->id, NULL, update, NULL);
    sock->id = socket(AF_INET, SOCK_STREAM, 0);
    
    sock->socket.sin_addr.s_addr = af_inet("127.0.0.1")
    sock->socket.sin_family = AF_INET;
    sock->socket.sin_port = htons(port);
    sock->port = port;

    if(connect(sock->id, (struct sockaddr*)&sock->socket, sizeof(sock->socket)) < 0){
        return 0;
    }

    char* message = (char*)malloc((4 + nLength(port)) * sizeof(char));
    sprintf(message, "new:%i", port);
    send(mainSocket->id, message, strlen(message), 0);
    free(message);
    message = (char*)malloc(4 * sizeof(char));
    if(recv(sock->id, message, 4, 0) < 0){
        return 0;
    }

    if(!strcmp(message, "fail")){
        return 0;
    }
    free(message);

    int* old = usedSockets;
    sockSize++;
    usedSockets = (int*)realloc(usedSockets, sockSize * sizeof(int));
    if(old != usedSockets){
        free(old);
    }
    usedSockets[sockSize - 1] = port;

    return sock;
}

void freeNetSocket(net_t* sock){
    char* message = (char*)malloc((4 + nLength(sock->port)) * sizeof(char));
    sprintf(message, "rem:%i", sock->port);
    write(mainSocket->id, message, strlen(message));
    free(message);
    message = (char*)malloc(4 * sizeof(char));
    if(recv(mainSocket->id, message, 4, 0) < 0){
        return 0;
    }

    int* old = usedSockets;
    for(int i = 0; i < sockSize; i++){
        if(usedSockets[i] == sock->port){
            if(i == sockSize - 1){
                break;
            }
            usedSockets[i] = usedSockets[i + 1];
        }   
    }
    sockSize--;
    usedSockets = (int*)realloc(usedSockets, sockSize * sizeof(int));
    if(old != usedSockets){
        free(old);
    }

    free(sock);
}