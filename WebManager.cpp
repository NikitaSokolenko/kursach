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
#include "ErrorTracker.h"

extern ErrorTracker ErrTr;

using namespace std;

WebManager::WebManager(unsigned int port){
	try{
    listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener<0){
		throw std::invalid_argument(std::string("Socket creation error"));}
	} catch(std::exception& e){
			ErrTr.write_log(e.what(), true);
			exit(1);		
	}
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(Adress);
}

int WebManager::new_bind(){
int rc = bind(listener, (struct sockaddr *)&addr, sizeof(addr));
try{
	if (rc<0){
		throw std::invalid_argument(std::string("Socket bind error"));}
} catch(std::exception& e){
			ErrTr.write_log(e.what(), true);
			exit(1);		
	}
	return rc;
}

void WebManager::start_listening(){
int rc = listen(listener, 1);
try{
	if (rc<0){
		throw std::invalid_argument(std::string("Listening error"));}
} catch(std::exception& e){
			ErrTr.write_log(e.what(), true);
			exit(1);		
	}
}

int WebManager::accepting(){
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof (sockaddr_in);
	int rc = accept(listener,  (sockaddr*)(client_addr), &len);
	try{
	if (rc<0){
		throw std::invalid_argument(std::string("Accepting error"));}
} catch(std::exception& e){
			ErrTr.write_log(e.what(), false);		
	}
    return rc;
}

int WebManager::receiving(int sock, void*buf, int size){
	int rc = recv(sock, buf, size, 0);
	try{
	if (rc<0){
		throw std::invalid_argument(std::string("Receiving error"));}
} catch(std::exception& e){
			ErrTr.write_log(e.what(), false);
			close(sock);		
	}
    return rc;
}

void WebManager::sending(int sock, void*buf, int sizeb){
	int rc = send(sock, buf, sizeb, 0);
	try{
	if (rc<0){
		throw std::invalid_argument(std::string("Sending error"));}
} catch(std::exception& e){
			ErrTr.write_log(e.what(), false);
			close(sock);		
	}
}

void WebManager::closing(int sock){
    close(sock);
}
