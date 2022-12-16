#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "WebManager.h"

using namespace std;

WebManager::WebManager(unsigned int port){
    listener = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(Adress);
}

int WebManager::new_bind(){
    return bind(listener, (struct sockaddr *)&addr, sizeof(addr));
}

void WebManager::start_listening(){
    listen(listener, 1);
}

int WebManager::accepting(){
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof (sockaddr_in);
    return accept(listener,  (sockaddr*)(client_addr), &len);
}

int WebManager::receiving(int sock, void*buf, int size){
    return recv(sock, buf, size, 0);
}

void WebManager::sending(int sock, void*buf, int sizeb){
    send(sock, buf, sizeb, 0);
}

void WebManager::closing(int sock){
    close(sock);
}