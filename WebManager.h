#pragma once

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

class WebManager
{
private:
    unsigned int Port;
    const char* Adress = "127.0.0.1";
    struct sockaddr_in addr;
    int listener;
    std::vector <int> sockets;
public:
    WebManager(unsigned int port);
    void start_listening();
    int new_bind();
    int accepting();
    int receiving(int sock, void*buf, int size);
    void sending(int sock, void*buf, int sizeb);
};
