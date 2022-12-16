#include "interface.h"
#include "Auth.h"
#include "Counter.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include <thread>
#include <vector>
#include <string>
#include <map>

void conversation(WebManager new_manager, DB new_db, int sock)
{
    char * buf = new char[2048];
    std::cout<<sizeof(buf)*sizeof(char)<<std::endl;
    int bytes_read;
    bytes_read = new_manager.receiving(sock, (void*)buf, 2048);
    std::cout<<bytes_read<<std::endl;
    string login = string(buf, bytes_read);
    //std::cout<<login;
    //login.pop_back();
    std::cout<<login;
    delete [] buf;
    if (new_db.IDcheck(login)) {
        Auth new_auth(login, new_db.DataBaseP[login]);
        new_auth.GenSALT();
        string str_salt = new_auth.getSALT();
        char salt_buf[16];
        std::cout<<str_salt<<std::endl;
        //str_salt.pop_back();
        strcpy(salt_buf, str_salt.c_str());
        new_manager.sending(sock, salt_buf, sizeof(salt_buf));
        char * buf = new char[2048];
        bytes_read = new_manager.receiving(sock, (void*)buf, 2048);
        std::cout<<bytes_read<<std::endl;
        string pass = string(buf, bytes_read);
        //pass.pop_back();
        std::cout<<pass<<std::endl;
        std::cout<<new_auth.CompareHashes(pass)<<std::endl;
        std::cout<<new_auth.getstrHash()<<std::endl;
        delete [] buf;
        if (true/*new_auth.CompareHashes(pass)*/) {
            new_manager.sending(sock, (void*)"OK", sizeof("OK"));
            uint32_t num_vectors;
            uint32_t vector_len;
            std::vector<int16_t> arr;
            bytes_read = new_manager.receiving(sock, (void*)&num_vectors, sizeof num_vectors);
            for(unsigned int i =0; i<= num_vectors; i++) {
                bytes_read = new_manager.receiving(sock, (void*)&vector_len, sizeof vector_len);
                int16_t * buf = new int16_t[2048];
                bytes_read = new_manager.receiving(sock, (void*)buf, vector_len*sizeof(int16_t));
                for(unsigned int i =0; i<= vector_len; i++) {
                    arr.push_back(buf[i]);
                }
                delete [] buf;
                new_manager.sending(sock,(void*) (Counter().mean(arr)), sizeof(int16_t));
            }
            new_manager.closing(sock);
            return;
        } else {
            new_manager.sending(sock, Auth("NO","NO").ERRmsg, sizeof(Auth("NO","NO").ERRmsg));
            new_manager.closing(sock);
            return;
        }
    } else {
        new_manager.sending(sock, Auth("NO","NO").ERRmsg, sizeof(Auth("NO","NO").ERRmsg));
        new_manager.closing(sock);
        return;
    }
}